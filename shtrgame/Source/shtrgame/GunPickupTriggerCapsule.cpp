// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/UserWidget.h"
#include "GunPickupTriggerCapsule.h"

AGunPickupTriggerCapsule::AGunPickupTriggerCapsule() {

	// help:
	// https://forums.unrealengine.com/t/tick-function-not-triggering/124175/2
	PrimaryActorTick.bCanEverTick = true;

	// initialize components

	GunActorPlacementSceneComp = CreateDefaultSubobject<USceneComponent>( TEXT("GunActorPlacementSceneComponent") );
	
	// build component hierarchy
	SetRootComponent( GunActorPlacementSceneComp );

}

// Called when the game starts or when spawned
void AGunPickupTriggerCapsule::BeginPlay()
{
	Super::BeginPlay();
	
    // spawn gun actor
    if( GunActorClass ) {

	    GunActor = GetWorld()->SpawnActor<AGeneralGun>( GunActorClass );
		GunActor->AttachToComponent( GunActorPlacementSceneComp, FAttachmentTransformRules::KeepRelativeTransform );
		GunActor->SetOwner( this );

		// i set custom GunActor scale by editing GunActorPlacementSceneComp scale
		// via gui blueprint editor

    }

	// bind events
	
	// help:	
	// https://www.youtube.com/watch?v=H2I7I8blgn8
	
    OnActorBeginOverlap.AddDynamic( this, &AGunPickupTriggerCapsule::OnOverlapBegin );
    OnActorEndOverlap.AddDynamic( this, &AGunPickupTriggerCapsule::OnOverlapEnd );

}

void AGunPickupTriggerCapsule::OnOverlapBegin( AActor *OverlappedActor, AActor *OtherActor ) {

	UE_LOG( LogTemp, Log, TEXT("AGunPickupTriggerCapsule::OnOverlapBegin") );
	
	// make sure i collided with an actor that is being controlled
	// by my custom player or ai
	if( !( OtherActor->GetInstigatorController() ) ) {
		return;
	}
	
	SetVisibleInteractionPrompt( true );
	bPlayerIsCloseEnoughToInteract = true;
	
	// listen to the "interact" signal
	// from this player
	AAnotherCharacterPlayerController *CustomPlayerController = Cast<AAnotherCharacterPlayerController>( OtherActor->GetInstigatorController() );
	if( CustomPlayerController ) {
		CustomPlayerController->InteractPressSignatureInstance.AddDynamic( this, &AGunPickupTriggerCapsule::RespondToInteractSignatureInstancePress );
		}

}

void AGunPickupTriggerCapsule::OnOverlapEnd( AActor *OverlappedActor, AActor *OtherActor ) {
	
	SetVisibleInteractionPrompt( false );
	bPlayerIsCloseEnoughToInteract = false;
	
	// stop listening to the "interact" signal
	// from this player
	// because i don't understand, how to check if already listening
	AAnotherCharacterPlayerController *CustomPlayerController = Cast<AAnotherCharacterPlayerController>( OtherActor->GetInstigatorController() );
	if( CustomPlayerController ) {
		CustomPlayerController->InteractPressSignatureInstance.RemoveDynamic( this, &AGunPickupTriggerCapsule::RespondToInteractSignatureInstancePress );
		}

}

void AGunPickupTriggerCapsule::SetVisibleInteractionPrompt( bool SetVisible ) {

	// Shows and hides the interaction prompt.
	
	// make sure i have initialized the prompt
	if( !InteractPrompt ) {
		
		// reused code from CO2301 lab 9
	
		// create the widget for the player, but don't show it yet
		if( InteractPromptClass ) {
			InteractPrompt = CreateWidget( UGameplayStatics::GetPlayerController( GetWorld(), 0 ), InteractPromptClass );
			}
		else {
			// no class and no widget
			return;
		}

	}

	if( SetVisible ) {
		// show interaction prompt

		if( !( InteractPrompt->IsInViewport() ) ) {
			InteractPrompt->AddToViewport( GUIPromptLayer );
		}

		return;
	
	}

	// hide interaction prompt

	if( InteractPrompt->IsInViewport() ) {
		InteractPrompt->RemoveFromViewport();
	}

}

void AGunPickupTriggerCapsule::SelfTerminate() {

	if( GunActor ) {
		GunActor->Destroy();
	}

	if( InteractPrompt ) {
		// ???
		InteractPrompt->Destruct();
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

void AGunPickupTriggerCapsule::RespondToInteractSignatureInstancePress( AAnotherCharacterPlayerController *CustomPlayerController ) {

	//UE_LOG( LogTemp, Warning, TEXT("AGunPickupTriggerCapsule::RespondToInteractSignatureInstancePress") );

	// make sure player is close enough to interact with it
	if( !bPlayerIsCloseEnoughToInteract ) {
		return;
		}

	// i end up here only when i am within the trigger box
	// and press appropriate button
		
	SetVisibleInteractionPrompt( false );
	bPlayerIsCloseEnoughToInteract = false;

	if( InteractSound ) {
		UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		InteractSound,
		GetActorLocation(),
		1.0f, 1.0f, 0.0f
		);
	}

	// tell the controller to change gun
	//AAnotherCharacterPlayerController *CustomPlayerController = Cast<AAnotherCharacterPlayerController>( UGameplayStatics::GetPlayerController( GetWorld(), 0 ) );
	CustomPlayerController->SetCurrentGunClass( GunActorClass );

	// i no longer need this trigger box
	// TODO:
	// make it fly away into the sky like a rocket
	SelfTerminate();

}
