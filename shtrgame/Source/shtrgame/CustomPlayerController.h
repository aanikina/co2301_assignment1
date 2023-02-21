// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WalkingTeapot.h"
#include "CustomPlayerController.generated.h"

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
	virtual void CallLook( float Value );
	
	virtual void CallFireTriggerPull();
	virtual void CallFireTriggerRelease();
	
	virtual void CallDashPress();
	virtual void CallDashRelease();
	
	AWalkingTeapot *PawnToBeMoved = nullptr;

	// a reference to a wall - in the future player will
	// collide with different walls,
	// during that collision this variable will
	// be updated
	// same goes for the seconds counter
	AActor *LastUsedWall = nullptr;
	float LastUsedWallSeconds = -1.0f; // meaningless for now

	UPROPERTY( EditAnywhere )
		float DelayBetweenWallCollisionSnapping = 1.0f; // seconds

	///*
	// reused code from CO2301 lab 9

	UPROPERTY( EditAnywhere )
	    TSubclassOf<UUserWidget> CrosshairHUDClass;
	UPROPERTY()
	    UUserWidget *CrosshairWidget;
	//*/
	
};
