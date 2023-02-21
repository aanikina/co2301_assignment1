// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "CustomPlayerController.h"
#include "TriggerWall.generated.h"

// help:
// https://unrealcpp.com/trigger-box/

UCLASS()
class SHTRGAME_API ATriggerWall : public ATriggerBox
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	ATriggerWall();

	UFUNCTION()
		void OnOverlapBegin(
			AActor *OverlappedActor,
			AActor *OtherActor
			);
		/*
		void OnOverlapBegin(
			UPrimitiveComponent *OverlappedComponent, 
            AActor *OtherActor, 
            UPrimitiveComponent *OtherComp, 
            int32 OtherBodyIndex, 
            bool bFromSweep, 
            const FHitResult &SweepResult
			);
		*/

	UFUNCTION()
		void OnOverlapEnd(
			AActor *OverlappedActor,
			AActor *OtherActor
			);
		/*
		void OnOverlapEnd(
			class UPrimitiveComponent *OverlappedComp,
			class AActor *OtherActor,
			class UPrimitiveComponent *OtherComp,
			int32 OtherBodyIndex
			);
		*/

	// reused code from WalkableWall actor

	UPROPERTY( VisibleAnywhere )
		UStaticMeshComponent* StaticMeshComp;
	
};
