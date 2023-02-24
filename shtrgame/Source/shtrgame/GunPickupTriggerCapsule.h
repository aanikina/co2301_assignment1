// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerCapsule.h"
#include "GeneralGun.h"
#include "AnotherCharacterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GunPickupTriggerCapsule.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API AGunPickupTriggerCapsule : public ATriggerCapsule
{
	GENERATED_BODY()

public:

	AGunPickupTriggerCapsule();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY( EditAnywhere )
		TSubclassOf<AGeneralGun> CurrentGunClass = nullptr;
		
	// this will be shown in the world
	UPROPERTY( VisibleAnywhere )
		AGeneralGun *GunActor = nullptr;
		
	UPROPERTY( VisibleAnywhere )
		class USceneComponent* GunPlacementSceneComp;

	// reused code from CO2301 lab4

	UFUNCTION()
		void OnOverlapBegin(
			AActor *OverlappedActor,
			AActor *OtherActor
			);

	UFUNCTION()
		void OnOverlapEnd(
			AActor *OverlappedActor,
			AActor *OtherActor
			);
			
	UPROPERTY( EditAnywhere )
	    TSubclassOf<UUserWidget> InteractWidgetClass;
	UPROPERTY( VisibleAnywhere )
	    UUserWidget *InteractWidget;
	
	UFUNCTION()
		void RespondToInteractSignatureInstancePress(); // AActor* HitActor, UPrimitiveComponent* HitComponent, const FVector& ImpactPoint, const FVector& ImpactNormal, FName HitBoneName, const FHitResult& HitResult)

};
