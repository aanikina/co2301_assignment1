// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Delegates/Delegate.h"
#include "AnotherCharacterPlayerController.generated.h"

// this is needed for a custom signal-slot definition
// help:
// https://unreal.gg-labs.com/wiki-archives/macros-and-data-types/delegates-in-ue4-raw-c++-and-bp-exposed
// https://forums.unrealengine.com/t/declare-dynamic-multicast-delegate-error-no-storage-class-or-type-specifier/431695
// https://forums.unrealengine.com/t/event-dispatchers-explained-finally/55570
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FInteractPressSignature );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FCurrentGunClasChangedSignature, TSubclassOf<AGeneralGun>, NewGunClass );

/*
This custom Player Controller
- can remember currently chosen gun
- can send multicast signal "player pressed 'Interact' button!"
*/
UCLASS()
class SHTRGAME_API AAnotherCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	
	void InteractPressEvent();
	void InteractReleaseEvent();

	// player will start either empty-handed or with this gun
	UPROPERTY( EditAnywhere )
		TSubclassOf<AGeneralGun> CurrentGunClass = nullptr;

public:
		
	virtual void SetupInputComponent();

	// allow others to access player's gun settings
	UFUNCTION()
		TSubclassOf<AGeneralGun> GetCurrentGunClass();
	UFUNCTION()
		void SetCurrentGunClass( TSubclassOf<AGeneralGun> NewGunClass );

	// this is a custom signal-slot
	FInteractPressSignature InteractPressSignatureInstance;
	FCurrentGunClasChangedSignature CurrentGunClasChangedSignatureInstance;

};
