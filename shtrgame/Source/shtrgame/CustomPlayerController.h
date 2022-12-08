// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WalkingTeapot.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()

// reused code from CO2301 lab8

protected:

	virtual void BeginPlay() override;

public:

	virtual void SetupInputComponent();
	
	virtual void CallDrive( float Value );
	virtual void CallStrafe( float Value );
	virtual void CallTurn( float Value );

	AWalkingTeapot *PawnToBeMoved;
	
};
