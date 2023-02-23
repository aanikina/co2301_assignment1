// Fill out your copyright notice in the Description page of Project Settings.


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

	// help:	
	// https://www.youtube.com/watch?v=H2I7I8blgn8
	
    OnActorBeginOverlap.AddDynamic( this, &AGunPickupTriggerCapsule::OnOverlapBegin );
    OnActorEndOverlap.AddDynamic( this, &AGunPickupTriggerCapsule::OnOverlapEnd );

}

void AGunPickupTriggerCapsule::OnOverlapBegin( AActor *OverlappedActor, AActor *OtherActor ) {

	UE_LOG( LogTemp, Log, TEXT("AGunPickupTriggerCapsule::OnOverlapBegin") );
	
	// make sure i collided with an actor that is being controlled
	// by enther player or ai
	if( !OtherActor->GetInstigatorController() ) {
		return;
	}

	// i'm sure this is my custom player controller
	AAnotherCharacterPlayerController *PlayerController = Cast<AAnotherCharacterPlayerController>( OtherActor->GetInstigatorController() );

	PlayerController->SetCurrentGunClass( CurrentGunClass );

}

void AGunPickupTriggerCapsule::OnOverlapEnd( AActor *OverlappedActor, AActor *OtherActor ) {

	UE_LOG( LogTemp, Log, TEXT("AGunPickupTriggerCapsule::OnOverlapEnd") );

}
