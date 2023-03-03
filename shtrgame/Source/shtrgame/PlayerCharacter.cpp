// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// initialize components

	CameraComp = CreateDefaultSubobject<UCameraComponent>( TEXT("CameraComponent") );
	CameraSpringArmComp = CreateDefaultSubobject<USpringArmComponent>( TEXT("CameraSpringArmComponent") );

	// build component hierarchy

	CameraSpringArmComp->SetupAttachment( RootComponent );
	CameraComp->SetupAttachment( CameraSpringArmComp, USpringArmComponent::SocketName );

	// change maximum speed
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// remember game mode
	GameModeRef = Cast<AshtrgameGameModeBase>(
		UGameplayStatics::GetGameMode( GetWorld() )
		);

	// player/ai controllers appear only upon begin play - not
	// in the constructor

	// i want to remember this upcasted controller because
	// otherwise i will have to upcast it many times
	CustomPlayerController = Cast<AAnotherCharacterPlayerController>( GetController() );
	CustomBotController = Cast<ACustomAIController>( GetController() );
	
	if( CustomPlayerController ) {
		// i want to do some things if this is a player,
		// not ai
		
		// listen to the "interact" signal
		// from current custom player controller
		CustomPlayerController->CurrentGunClasChangedSignatureInstance.AddDynamic( this, &APlayerCharacter::RespondToCurrentGunClasChangedSignatureInstance );

		}
	
	if( CustomBotController ) {
		// i want to do some things if this is a ai,
		// not player
		
		// nothing yet

		}

}

float APlayerCharacter::GetStatsHP() {

    return StatsHP;

}

void APlayerCharacter::RespondToCurrentGunClasChangedSignatureInstance( TSubclassOf<AGeneralGun> NewGunClass ) {

	//UE_LOG( LogTemp, Warning, TEXT("APlayerCharacter::RespondToCurrentGunClasChangedSignatureInstance") );

	// i end up here only when relevant instance of my custom player controller
	// says it changed current gun class
		
	// i want to discard my current gun actor
	if( CurrentGun ) {
		// if i end up here
		// it means i have previously drawn my gun - i'm not walking around empty handed
		// so i want to draw my gun again after replacing it
		CurrentGun->Destroy();
		CurrentGun = nullptr;
		DrawCurrentGun();
	}

}

/*
// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// these events manipulate a player controller
	// that is specified in the project settings??

	// reused code from CO2301 lab2, lab8
	// help:
	// https://youtu.be/xZjZimU31wc
	
	PlayerInputComponent->BindAxis( TEXT("Drive"), this, &APlayerCharacter::DriveEvent );
	PlayerInputComponent->BindAxis( TEXT("Turn"), this, &APlayerCharacter::AddControllerYawInput );
	PlayerInputComponent->BindAxis( TEXT("Strafe"), this, &APlayerCharacter::StrafeEvent );
	PlayerInputComponent->BindAxis( TEXT("Look"), this, &APlayerCharacter::AddControllerPitchInput );
	
	PlayerInputComponent->BindAction( TEXT("Fire"), IE_Pressed, this, &APlayerCharacter::FireTriggerPullEvent );
	PlayerInputComponent->BindAction( TEXT("Fire"), IE_Released, this, &APlayerCharacter::FireTriggerReleaseEvent );
	
	PlayerInputComponent->BindAction( TEXT("Dash"), IE_Pressed, this, &APlayerCharacter::DashPressEvent );
	PlayerInputComponent->BindAction( TEXT("Dash"), IE_Released, this, &APlayerCharacter::DashReleaseEvent );
	
	PlayerInputComponent->BindAction( TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::JumpPressEvent );
	PlayerInputComponent->BindAction( TEXT("Jump"), IE_Released, this, &APlayerCharacter::JumpReleaseEvent );
	
	PlayerInputComponent->BindAction( TEXT("DrawGun"), IE_Pressed, this, &APlayerCharacter::DrawGunPressEvent );
	//PlayerInputComponent->BindAction( TEXT("DrawGun"), IE_Released, this, &APlayerCharacter::DrawGunReleaseEvent );

}

void APlayerCharacter::DriveEvent( float AxisValue ) {

	// reused code from CO2301 lab2

	// help:
	// https://forums.unrealengine.com/t/how-to-normalize-a-vector-in-c/436855
	AddMovementInput( GetActorForwardVector().GetSafeNormal(), AxisValue, false );

	//UE_LOG( LogTemp, Warning, TEXT("vector %s, scale %f"), *(GetActorForwardVector().GetSafeNormal()).ToString(), MoveSpeed*AxisValue*DashSpeed );

}

void APlayerCharacter::StrafeEvent( float AxisValue ) {

	AddMovementInput( GetActorRightVector(), AxisValue, false );

}

void APlayerCharacter::BrieflyShowEmptyHanded() {
		
	// help:
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/FTimerHandle/
	if( FireCooldownTimerHandle.IsValid() ) {
		// timer is running, not doing anything
		return;
	}

	SetVisibleEmptyHanded( true );

	// reused code from CO2301 lab 7
	
	GetWorld()->GetTimerManager().SetTimer(
		FireCooldownTimerHandle,
		this, // which object runs the timer
		&APlayerCharacter::FireCooldownTimerRanOut, // what to do when the timer runs out
		BaseFireCooldownTime, // timer duration
		false // loop the timer?
	);

}

void APlayerCharacter::FireCooldownTimerRanOut() {

	// this will allow to set this timer again
	FireCooldownTimerHandle.Invalidate();
	
	SetVisibleEmptyHanded( false );

}

void APlayerCharacter::DashCooldownTimerRanOut() {

	// this will allow to set this timer again
	DashCooldownTimerHandle.Invalidate();

}

void APlayerCharacter::SetVisibleEmptyHanded( bool SetVisible ) {

	// Shows and hides the interaction prompt.
	
	// make sure i have initialized the prompt
	if( !EmptyHandedWidget ) {
		
		// reused code from CO2301 lab 9
	
		// create the widget for the player, but don't show it yet
		if( EmptyHandedWidgetClass ) {
			EmptyHandedWidget = CreateWidget( CustomPlayerController, EmptyHandedWidgetClass );
			}
		else {
			// no class and no widget
			return;
		}

	}

	if( SetVisible ) {
		// show interaction prompt

		if( !( EmptyHandedWidget->IsInViewport() ) ) {
			EmptyHandedWidget->AddToViewport( GUILayer );
		}

		return;
	
	}

	// hide interaction prompt

	if( EmptyHandedWidget->IsInViewport() ) {
		EmptyHandedWidget->RemoveFromViewport();
	}

}

void APlayerCharacter::DrawCurrentGun() {

	// Creates usable gun in the character's hands.
	
	// make sure haven't drawn gun previously
	if( CurrentGun ) {
		// i want to hide my current gun away

		CurrentGun->Destroy();
		CurrentGun = nullptr;
		
		if( CustomPlayerController ) {
			// i'm a player
			CustomPlayerController->SetVisibleCrosshair( false );
			}

		return;

	}

	// make sure i know what type of gun i have
	if( CustomPlayerController ) {
		// i'm a player
		if( !( CustomPlayerController->GetCurrentGunClass() ) ) {
			// no gun
			BrieflyShowEmptyHanded();
			return;
		}
	} else if( CustomBotController ) {
		// i'm a bot
		if( !( CustomBotController->GetCurrentGunClass() ) ) {
			// no gun
			BrieflyShowEmptyHanded();
			return;
		}
	}

	// help:
	// https://forums.unrealengine.com/t/attach-actor-to-socket-via-c/8167
	// https://forums.unrealengine.com/t/how-to-get-character-mesh-in-c-from-character-blueprint/325816/3
	// reused code from example in CO2301 internship discord

	CurrentGun = GetWorld()->SpawnActor<AGeneralGun>( CustomPlayerController->GetCurrentGunClass() );

	CurrentGun->AttachToComponent( GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponRSocket") );
    CurrentGun->SetOwner( this );
	
	// useless, disabled gun collision
	// in the blueprint editor
	//GetMesh()->IgnoreActorWhenMoving( this->CurrentGun, true );
	//GetMesh()->IgnoreActorWhenMoving( CurrentGun, true );
	
	if( CustomPlayerController ) {
		// i'm a player
		CustomPlayerController->SetVisibleCrosshair( true );
	}

}

void APlayerCharacter::FireTriggerPullEvent() {

	// help:
	// https://www.orfeasel.com/single-line-raycasting/
	// https://cpp.hotexamples.com/examples/-/-/GetActorEyesViewPoint/cpp-getactoreyesviewpoint-function-examples.html
	
	if( !CurrentGun ) {
		// no gun, dumbfounded
		BrieflyShowEmptyHanded();
		// TODO
		// lost travolta
		return;
	}

	// make sure gun has actually fired
	bool bFireTriggerPulledSuccessfully = CurrentGun->FireTriggerPull();
	if( !bFireTriggerPulledSuccessfully ) {
		return;
	}

	// draw a line between attacker and victim

	// i pretend i want to draw a line between camera and something far away at the
	// center of the screen - i start at CameraLocation and arrive at CamSightLineEnd	
	FRotator CameraRotation = CameraComp->GetComponentRotation();
	FVector CameraLocation = CameraComp->GetComponentLocation();
	FVector CamSightLineEnd = CameraLocation + ( CameraRotation.Vector() ) * CurrentGun->GetFireDistance();

	// but actually i want to draw a line between
	FVector StartLocation = CameraLocation;
    FVector EndLocation = CamSightLineEnd;
	
    // boolean parameter forces lines to be persistent so the raycast is not erased in millisecond
    // last parameter is the width of the lines
    //DrawDebugLine( GetWorld(), StartLocation, EndLocation, FColor::Orange, true, -1, 0, 1.0f );

	/*
	// apperently this checks if somebody hit me, not if i hit somebody
	// useless
	// help:
	// https://docs.unrealengine.com/5.1/en-US/API/Runtime/Engine/GameFramework/AActor/ActorLineTraceSingle/
	FHitResult RaycastHitResult;
    GetOwner()->ActorLineTraceSingle(
		RaycastHitResult,
		StartLocation, EndLocation,
		ECollisionChannel::ECC_WorldDynamic, CollisionParameters
		);
	*/

	// perform an actual line trace to determine who got shot
	
	// help:
	// reused code from CO2301 lecture about raytracing
	// http://jollymonsterstudio.com/2019/01/06/unreal-engine-c-fundamentals-linetracesinglebychannel-and-friends-drawdebugbox-drawdebugline-fhitresult-and-vrandcone/
	
	//FCollisionQueryParams CollisionParameters;
	FCollisionQueryParams TraceParams( FName(TEXT("InteractTrace")), true, NULL );

	FHitResult RaycastHitResult;
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(
		RaycastHitResult,
		StartLocation,
		EndLocation,
		ECC_GameTraceChannel13,
		TraceParams
	);
 
	// make sure i actually hit an actor
	if( !bIsHit ) {
		// nothing got hit, not doing anything
		//UE_LOG( LogTemp, Warning, TEXT("nothing at all got hit") );
		return;
	}
	AActor *HitActor = RaycastHitResult.GetActor();
	if( !HitActor ) {
		// no actor got hit, not doing anything
		//UE_LOG( LogTemp, Warning, TEXT("no actor got hit") );
		return;
	}
	//UE_LOG( LogTemp, Warning, TEXT("Actor %s: AAAAAAAAAAAAAAAAaa"), HitActor ); // function GetName() fails
	
	// i want to apply damage to the thing i shot
	
	// reused code from example in CO2301 internship discord

	float DamageDealt = CurrentGun->GetDamage();

	// create proper event
	FHitResult DamageEventHitResult;
	FPointDamageEvent DamageEvent( DamageDealt, DamageEventHitResult, EndLocation, nullptr );
	
	// send it to someone who can receive it
	// apparently those who can not receive it silently ignore it
	HitActor->TakeDamage(
		DamageDealt, // why do i duplicate it? i already have it in the DamageEvent
		DamageEvent,
		GetController(), // not upcasted version of my custom player/ai controller
		this
		);

}

void APlayerCharacter::FireTriggerReleaseEvent() {
	
	//UE_LOG( LogTemp, Warning, TEXT("FireTriggerReleaseEvent") );
	
	if( !CurrentGun ) {
		// no gun, dumbfounded

		return;

	}
	
	CurrentGun->FireTriggerRelease();

}

void APlayerCharacter::DashPressEvent() {
	//UE_LOG( LogTemp, Warning, TEXT("DashPressEvent") );
	
	if( DashCooldownTimerHandle.IsValid() ) {
		// timer is still counting, not doing anything
		return;
	}

	// set new timer
	GetWorld()->GetTimerManager().SetTimer(
		DashCooldownTimerHandle,
		this, // which object runs the timer
		&APlayerCharacter::DashCooldownTimerRanOut, // what to do when the timer runs out
		BaseDashCooldownTime, // timer duration
		false // loop the timer?
	);

	// i want to rush in the direction of currently held keyboard keys
	// or forward

	FVector Velocity = GetVelocity().GetSafeNormal();
	//UE_LOG( LogTemp, Warning, TEXT("velocity %s"), *Velocity.ToString() );
	if( ( Velocity.X==0.0f ) && ( Velocity.Y==0.0f ) && ( Velocity.Z==0.0f ) ) {
		Velocity = GetActorForwardVector().GetSafeNormal();
	}

	// help:
	// https://www.youtube.com/watch?v=GNkQK-lu-rQ
	// https://forums.unrealengine.com/t/can-t-set-getcharactermovement-borientedrotationtomovement-true-in-my-character-class/138458
	LaunchCharacter( Velocity*DashSpeed, true, true );

}

void APlayerCharacter::DashReleaseEvent() {
	//UE_LOG( LogTemp, Warning, TEXT("DashReleaseEvent") );
	
	// help:
	// https://www.youtube.com/watch?v=GNkQK-lu-rQ
	//GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;

}

void APlayerCharacter::DrawGunPressEvent() {

	//UE_LOG( LogTemp, Warning, TEXT("DrawGunPressEvent") );

	DrawCurrentGun();

}
void APlayerCharacter::DrawGunReleaseEvent() {

	//UE_LOG( LogTemp, Warning, TEXT("DrawGunReleaseEvent") );

}

void APlayerCharacter::JumpPressEvent() {
	
	// call already implemented jump function
	// i don't like it - feels like slowmotion
	Jump();

	//LaunchCharacter( GetActorUpVector().GetSafeNormal()*JumpSpeed, true, true );

}
void APlayerCharacter::JumpReleaseEvent() {

	UE_LOG( LogTemp, Warning, TEXT("JumpReleaseEvent") );
	
}

AGeneralGun *APlayerCharacter::GetCurrentGun() {
	
	return CurrentGun;

}

void APlayerCharacter::TakeDamageAnimationTimerRanOut() {

	// this will allow to set this timer again
	TakeDamageAnimationTimerHandle.Invalidate();
	
	if( CustomPlayerController ) {
		GameModeRef->PlayerDead();
	} else {
		GameModeRef->KillScored();
	}

	Destroy();

}

float APlayerCharacter::TakeDamage( float DamageAmount, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser ) {
	
	UE_LOG( LogTemp, Warning, TEXT("APlayerCharacter::TakeDamage") );

	// apply the damage

	StatsHP -= DamageAmount;
	
	// help:
	// https://forums.unrealengine.com/t/how-to-setup-and-play-animation-strictly-using-c/131391/8
	if( TakeDamageAnimation ) {
		GetMesh()->SetAnimation( DeathAnimation );
		GetMesh()->SetPlayRate( 1.0f );
		GetMesh()->Play(true);
	}

	if( StatsHP<=0.0f ) {

		// help:
		// https://forums.unrealengine.com/t/how-to-setup-and-play-animation-strictly-using-c/131391/8
		// https://forums.unrealengine.com/t/how-can-i-use-a-delay-or-a-sleep-in-c/286782/2
		if( DeathAnimation ) {

			GetMesh()->SetAnimation( DeathAnimation );
			GetMesh()->SetPlayRate( 1.0f );
			GetMesh()->Play(true);
			//FPlatformProcess::Sleep( 2.0f ); // freezes everything

		}
		
		// set new timer
		GetWorld()->GetTimerManager().SetTimer(
			TakeDamageAnimationTimerHandle,
			this, // which object runs the timer
			&APlayerCharacter::TakeDamageAnimationTimerRanOut, // what to do when the timer runs out
			2.0f, // timer duration
			false // loop the timer?
		);
		// i want to destroy self and
		// change game mode only after timer runs out
		//Destroy();

	}

	// do some custom things
	
	if( CustomBotController ) {
		// this character is controlled by ai

		CustomBotController->RemeberThatWasAttackedBy( this );
	
	}

	return DamageAmount;

}
