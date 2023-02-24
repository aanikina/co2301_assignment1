// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GeneralGun.h"
#include "Delegates/Delegate.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
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

public:

	AAnotherCharacterPlayerController();

private:
	
	void InteractPressEvent();
	void InteractReleaseEvent();

	// for how many seconds the widgets are visible
	UPROPERTY( EditAnywhere )
		float BaseWidgetShowTime = 0.3f; // seconds

	UPROPERTY( EditAnywhere )
		TSubclassOf<AGeneralGun> CurrentGunClass = nullptr;
	
	// chooses gun/none widget and toggles it
	void SetVisibleCurrentGunWidget( bool Visible );
	// hides widget
	void TimerHandleRanOut();
		
	// reused code from CO2301 lab 7

	FTimerHandle TimerHandle;

public:
		
	virtual void SetupInputComponent();

	UFUNCTION()
		TSubclassOf<AGeneralGun> GetCurrentGunClass();
	UFUNCTION()
		void SetCurrentGunClass( TSubclassOf<AGeneralGun> NewGunClass );

	//UPROPERTY( VisibleAnywhere ) // no need to show this in blueprint
		FInteractPressSignature InteractPressSignatureInstance;
		
	UPROPERTY( EditAnywhere )
	    TSubclassOf<UUserWidget> GunEmptyWidgetClass;
	//UPROPERTY( VisibleAnywhere ) // no need to show this in blueprint
	    UUserWidget *CurrentGunWidget;
	
	// i want others to access it	
	void BrieflyShowCurrentGunWidget();
	// performs the choice betwee weapon icon and empty hand
	void ChooseCurrentGunWidget();

};
