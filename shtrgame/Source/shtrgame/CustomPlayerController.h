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

	AWalkingTeapot *PawnToBeMoved;

	/*
	// reused code from CO2301 lab 3
	
	// help:
	// https://stackoverflow.com/questions/59587928/tsubclassof-isnt-storing-the-class-type
	// https://docs.unrealengine.com/5.1/en-US/array-containers-in-unreal-engine/
	// https://forums.unrealengine.com/t/gethitresultundercursorforobjects-array/323982
	TArray< TEnumAsByte<EObjectTypeQuery> > WalkableClasses;
	//*/
	
};
