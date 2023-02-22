// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GeneralGun.h"
#include "AnotherCharacterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API AAnotherCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	
	UPROPERTY( EditAnywhere )
		float BaseGunSwitchCooldown = 5.0f; // seconds

public:

	UPROPERTY( EditAnywhere )
		TSubclassOf<AGeneralGun> CurrentGunClass = nullptr;

};
