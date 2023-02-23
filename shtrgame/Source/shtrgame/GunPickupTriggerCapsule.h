// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerCapsule.h"
#include "GeneralGun.h"
#include "AnotherCharacterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GunPickupTriggerCapsule.generated.h"

// failed attempt to create signal-slots thing for "press interact button"
// useless
// help:
// https://forums.unrealengine.com/t/event-dispatchers-explained-finally/55570
// https://unreal.gg-labs.com/wiki-archives/macros-and-data-types/delegates-in-ue4-raw-c++-and-bp-exposed
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FPlayerChoseToInteractDelegate, AAnotherCharacterPlayerController, *AnotherPlayerCharController );

/**
 * 
 */
UCLASS()
class SHTRGAME_API AGunPickupTriggerCapsule : public ATriggerCapsule
{
	GENERATED_BODY()

public:

	AGunPickupTriggerCapsule();

	// failed attempt to mix c++ with blueprints
	// and change this variable whenever user presses "interact" key
	// useless
	// help:
	// https://forums.unrealengine.com/t/edit-blueprint-variable-in-c/404466/3
	// https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/Blueprints/UserGuide/Variables/
	//UPROPERTY( EditAnywhere, BlueprintReadWrite )
	//	bool bInteractButtonIsPressed;

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
	
};
