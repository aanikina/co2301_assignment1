// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/UserWidget.h"
#include "GunPickupTriggerCapsule.h"

AGunPickupTriggerCapsule::AGunPickupTriggerCapsule() {

	// help:
	// https://forums.unrealengine.com/t/tick-function-not-triggering/124175/2
	PrimaryActorTick.bCanEverTick = true;

	// initialize components

	GunPlacementSceneComp = CreateDefaultSubobject<USceneComponent>( TEXT("GunPlacementSceneComponent") );
	
	// build component hierarchy
	SetRootComponent( GunPlacementSceneComp );

}

// Called when the game starts or when spawned
void AGunPickupTriggerCapsule::BeginPlay()
{
	Super::BeginPlay();
	
    // spawn gun actor
    if( CurrentGunClass ) {

	    GunActor = GetWorld()->SpawnActor<AGeneralGun>( CurrentGunClass );
		GunActor->AttachToComponent( GunPlacementSceneComp, FAttachmentTransformRules::KeepRelativeTransform );
		GunActor->SetOwner( this );

		// i set custom GunActor scale by editing GunPlacementSceneComp scale
		// via gui blueprint editor
    }

	// bind events
	
	// help:	
	// https://www.youtube.com/watch?v=H2I7I8blgn8
	
    OnActorBeginOverlap.AddDynamic( this, &AGunPickupTriggerCapsule::OnOverlapBegin );
    OnActorEndOverlap.AddDynamic( this, &AGunPickupTriggerCapsule::OnOverlapEnd );
	
	// listen to the "interact" signal
	// from the player
	AAnotherCharacterPlayerController *PlayerController = Cast<AAnotherCharacterPlayerController>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ) );
	if( PlayerController ) {
		PlayerController->InteractPressSignatureInstance.AddDynamic( this, &AGunPickupTriggerCapsule::RespondToInteractSignatureInstancePress );
		}

	// reused code from CO2301 lab 9
	
	// create the widget, but don't show it yet
	if( InteractWidgetClass ) {
		InteractWidget = CreateWidget( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), InteractWidgetClass );
		}

}

void AGunPickupTriggerCapsule::OnOverlapBegin( AActor *OverlappedActor, AActor *OtherActor ) {

	UE_LOG( LogTemp, Log, TEXT("AGunPickupTriggerCapsule::OnOverlapBegin") );
	
	// make sure i collided with an actor that is being controlled
	// by either player or ai
	if( !OtherActor->GetInstigatorController() ) {
		return;
	}
	
	SetVisibleInteractionPrompt( true );
	bPlayerIsAllowedToInteract = true;
	
	/*
	// i'm sure this is my custom player controller
	AAnotherCharacterPlayerController *PlayerController = Cast<AAnotherCharacterPlayerController>( OtherActor->GetInstigatorController() );
	
	SetVisibleInteractionPrompt( false );

	PlayerController->SetCurrentGunClass( CurrentGunClass );
	*/

}

void AGunPickupTriggerCapsule::OnOverlapEnd( AActor *OverlappedActor, AActor *OtherActor ) {
	
	SetVisibleInteractionPrompt( false );
	bPlayerIsAllowedToInteract = false;

}

void AGunPickupTriggerCapsule::SetVisibleInteractionPrompt( bool Visible ) {
	
	// make sure i have initialized the prompt
	if( !InteractWidget ) {
		return;
	}

	if( Visible ) {
		// show interaction prompt

		if( !InteractWidget->IsInViewport() ) {
			InteractWidget->AddToViewport( 10 ); // layer 10 just in case
		}

		return;
	
	}

	// hide interaction prompt

	if( InteractWidget->IsInViewport() ) {
		InteractWidget->RemoveFromViewport();
	}

}

void AGunPickupTriggerCapsule::SelfTerminate() {

	if( GunActor ) {
		GunActor->Destroy();
	}

	if( InteractWidget ) {
		// ???
		//InteractWidget->Destroy();
	}
	
	Destroy();

}

void AGunPickupTriggerCapsule::Tick( float DeltaTime ) {
	
	Super::Tick(DeltaTime);
	
	//UE_LOG( LogTemp, Warning, TEXT("AGunPickupTriggerCapsule::Tick") );

	if( GunActor ) {
	
		// rotate yaw
		GunActor->AddActorLocalRotation( FRotator( 0.0f, IdleRotationSpeed*DeltaTime, 0.0f ) );

		// up and down
		// this one is extremely slow: ChangingAngle*DeltaTime
		// so i use IdleHoverSpeed to speed it up
		float ChangingAngle = GunActor->GetActorRotation().Yaw;
		GunActor->AddActorLocalOffset( FVector( 0.0f, 0.0f, IdleHoverAmplitude*sinf(ChangingAngle*DeltaTime*IdleHoverSpeed) ) );
		
		//UE_LOG( LogTemp, Warning, TEXT("AGunPickupTriggerCapsule::Tick %f"), sinf(ChangingAngle*DeltaTime) );

	}

}

void AGunPickupTriggerCapsule::RespondToInteractSignatureInstancePress() {

	//UE_LOG( LogTemp, Warning, TEXT("AGunPickupTriggerCapsule::RespondToInteractSignatureInstancePress") );

	// make sure player is allowed to interact with it
	if( !bPlayerIsAllowedToInteract ) {
		return;
		}

	// i end up here only when i am within the trigger box
	// and press appropriate button
		
	SetVisibleInteractionPrompt( false );
	bPlayerIsAllowedToInteract = false;

	if( InteractSound ) {
		UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		InteractSound,
		GetActorLocation(),
		1.0f, 1.0f, 0.0f
		);
	}

	AAnotherCharacterPlayerController *PlayerController = Cast<AAnotherCharacterPlayerController>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ) );
	PlayerController->SetCurrentGunClass( CurrentGunClass );

	// i no longer need this trigger box
	SelfTerminate();

}

