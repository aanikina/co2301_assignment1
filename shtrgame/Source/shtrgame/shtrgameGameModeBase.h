// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "shtrgameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API AshtrgameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:

	FName GameoverLevel;

	UPROPERTY( EditAnywhere )
		int HowManyThingsToKill = 2;

	// reused code from CO2301 lab 4, 7

	UFUNCTION()
		void StartGame();
		
	UFUNCTION()
		void GameOver();

public:
		
	UFUNCTION()
		void KillScored();
		
	UFUNCTION()
		void PlayerDead();
	
};
