// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// initialize components

	CameraComp = CreateDefaultSubobject<UCameraComponent>( TEXT("CameraComponent") );
	CameraSpringArmComp = CreateDefaultSubobject<USpringArmComponent>( TEXT("CameraSpringArmComponent") );

	// build component hierarchy

	CameraSpringArmComp->SetupAttachment( RootComponent );
	CameraComp->SetupAttachment( CameraSpringArmComp, USpringArmComponent::SocketName );

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// player controllers appear only upon begin play - not
	// in the constructor

	// i want to remember this upcasted controller because
	// otherwise i will have to upcast it many times
	AnotherCharacterController = Cast<AAnotherCharacterPlayerController>(  GetController() );
	
	// controller may lack a gun in the beginning of the game
	if( AnotherCharacterController ) {
		// controller already has a gun
		APlayerCharacter::DrawCurrentGun();
	}

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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
	// useless
	//PlayerInputComponent->BindAction( TEXT("DrawGun"), IE_Released, this, &APlayerCharacter::DrawGunReleaseEvent );

}

void APlayerCharacter::DriveEvent( float AxisValue ) {

	// reused code from CO2301 lab2
	
	AddMovementInput( GetActorForwardVector()*AxisValue, MoveSpeed, false );
	
}

void APlayerCharacter::StrafeEvent( float AxisValue ) {

	AddMovementInput( GetActorRightVector()*AxisValue*MoveSpeed, 1.0f, false );

}

void APlayerCharacter::DrawCurrentGun() {

	// Creates usable gun in the character's hands.
	
	// make sure haven't drawn gun previously
	if( CurrentGun ) {
		return;
	}

	// make sure i know what type of weapon i have
	if( !AnotherCharacterController->GetCurrentGunClass() ) {
		return;
	}

	// help:
	// https://forums.unrealengine.com/t/attach-actor-to-socket-via-c/8167
	// https://forums.unrealengine.com/t/how-to-get-character-mesh-in-c-from-character-blueprint/325816/3
	// code example from CO2301 internship discord
			
	//FVector RightHandSocket = GetMesh()->GetSocketLocation("RightHandSocket");
	//FVector LeftHandSocket = GetMesh()->GetSocketLocation("LeftHandSocket");

	CurrentGun = GetWorld()->SpawnActor<AGeneralGun>( AnotherCharacterController->GetCurrentGunClass() );

	CurrentGun->AttachToComponent( GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponRSocket") );
    CurrentGun->SetOwner( this );
	
	// useless, disabled gun collision
	// in the blueprint editor
	//GetMesh()->IgnoreActorWhenMoving( this->CurrentGun, true );
	//GetMesh()->IgnoreActorWhenMoving( CurrentGun, true );

}

void APlayerCharacter::FireTriggerPullEvent() {

	// help:
	// https://www.orfeasel.com/single-line-raycasting/
	// https://cpp.hotexamples.com/examples/-/-/GetActorEyesViewPoint/cpp-getactoreyesviewpoint-function-examples.html
	
	if( !CurrentGun ) {
		// no gun, dumbfounded

		AnotherCharacterController->BrieflyShowCurrentGunWidget();
		return;

	}

	CurrentGun->FireTriggerPull();

	//UE_LOG( LogTemp, Warning, TEXT("FireTriggerPullEvent") );
	// https://forums.unrealengine.com/t/how-to-get-active-camera-object/331893/4

	//--------------------------------+++
	// Definitions.
	
    FHitResult HitResult;
	FVector StartLocation, EndLocation;
	FVector CamSightLineEnd;

	float RayLength;

	FCollisionQueryParams CollisionParameters;

	//--------------------------------+++
	// Actual code.
	
	FRotator CameraRotation = CameraComp->GetComponentRotation();
	FVector CameraLocation = CameraComp->GetComponentLocation();

    RayLength = 2000.0f;

	// i pretend i want to draw a line between camera and something far away at the
	// center of the screen - i start at CameraLocation and arrive at CamSightLineEnd
	CamSightLineEnd = CameraLocation + ( CameraRotation.Vector() )*RayLength;

	// but actually i want to draw a line between
	StartLocation = CameraLocation;
    EndLocation = CamSightLineEnd;

    GetOwner()->ActorLineTraceSingle(
		HitResult,
		StartLocation, EndLocation,
		ECollisionChannel::ECC_WorldDynamic, CollisionParameters
		);
 
    // boolean parameter forces lines to be persistent so the raycast is not erased in millisecond
    // last parameter is the width of the lines
    DrawDebugLine( GetWorld(), StartLocation, EndLocation, FColor::Orange, true, -1, 0, 1.0f );

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
	UE_LOG( LogTemp, Warning, TEXT("DashPressEvent") );
	MoveSpeed += DashSpeed;
}
void APlayerCharacter::DashReleaseEvent() {
	UE_LOG( LogTemp, Warning, TEXT("DashReleaseEvent") );
	MoveSpeed -= DashSpeed;
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
	Jump();

}
void APlayerCharacter::JumpReleaseEvent() {

	UE_LOG( LogTemp, Warning, TEXT("JumpReleaseEvent") );
	
}

AGeneralGun *APlayerCharacter::GetCurrentGun() {
	
	return CurrentGun;

}