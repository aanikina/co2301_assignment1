// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GeneralGun.h"
#include "Delegates/Delegate.h"
#include "AnotherCharacterPlayerController.generated.h"

// help:
// https://unreal.gg-labs.com/wiki-archives/macros-and-data-types/delegates-in-ue4-raw-c++-and-bp-exposed
// https://forums.unrealengine.com/t/declare-dynamic-multicast-delegate-error-no-storage-class-or-type-specifier/431695
// https://forums.unrealengine.com/t/event-dispatchers-explained-finally/55570
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FInteractPressSignature );
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FInteractPressSignature, class AActor*, HitActor );

/**
 * 
 */
UCLASS()
class SHTRGAME_API AAnotherCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	
	void InteractPressEvent();
	void InteractReleaseEvent();

	UPROPERTY( EditAnywhere )
		float BaseGunSwitchCooldown = 5.0f; // seconds

	UPROPERTY( EditAnywhere )
		TSubclassOf<AGeneralGun> CurrentGunClass = nullptr;

public:
		
	virtual void SetupInputComponent();

	UFUNCTION()
		TSubclassOf<AGeneralGun> GetCurrentGunClass();
	UFUNCTION()
		void SetCurrentGunClass( TSubclassOf<AGeneralGun> NewGunClass );

	UPROPERTY( VisibleAnywhere )
		FInteractPressSignature InteractPressSignatureInstance;

};
