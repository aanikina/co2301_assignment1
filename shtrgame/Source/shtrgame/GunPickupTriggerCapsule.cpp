// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/UserWidget.h"
#include "GunPickupTriggerCapsule.h"

AGunPickupTriggerCapsule::AGunPickupTriggerCapsule() {

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
    }

	// bind events
	
	// help:	
	// https://www.youtube.com/watch?v=H2I7I8blgn8
	
    OnActorBeginOverlap.AddDynamic( this, &AGunPickupTriggerCapsule::OnOverlapBegin );
    OnActorEndOverlap.AddDynamic( this, &AGunPickupTriggerCapsule::OnOverlapEnd );
	
	// listen to the "interact" signal
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
	
	// show interaction prompt
	if( InteractWidget ) {
		if( !InteractWidget->IsInViewport() ) {
			InteractWidget->AddToViewport( 10 ); // layer 10 just in case
		}
	}

	// i'm sure this is my custom player controller
	AAnotherCharacterPlayerController *PlayerController = Cast<AAnotherCharacterPlayerController>( OtherActor->GetInstigatorController() );

	// remove interact widget
	if( InteractWidget ) {
		if( InteractWidget->IsInViewport() ) {
			InteractWidget->RemoveFromViewport();
		}
	} 


	PlayerController->SetCurrentGunClass( CurrentGunClass );

}

void AGunPickupTriggerCapsule::OnOverlapEnd( AActor *OverlappedActor, AActor *OtherActor ) {
	
	// delete interaction prompt
	if( InteractWidget ) {
		if( InteractWidget->IsInViewport() ) {
			InteractWidget->RemoveFromViewport();
		}
	}

}

void AGunPickupTriggerCapsule::RespondToInteractSignatureInstancePress() {

	UE_LOG( LogTemp, Warning, TEXT("AGunPickupTriggerCapsule::RespondToInteractSignatureInstancePress") );

}

