// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GeneralGun.h"
#include "CustomAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API ACustomAIController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
private:

	// editable properties
	
	// player will start either empty-handed or with this gun
	UPROPERTY( EditAnywhere )
		TSubclassOf<AGeneralGun> CurrentGunClass;

	// other properties

	// reused code from CO2301 lab 11

	UPROPERTY()
		TArray<AActor*> Waypoints;

	// editable properties
	
	UPROPERTY( EditAnywhere )
		UBehaviorTree* EnemyBehaviorTree;

	// inviisble properties

	AActor* ChooseWaypoint();
	void RandomPatrol();

public:
	
	// functions

	void Tick( float DeltaTime ) override;

	void OnMoveCompleted(
		FAIRequestID RequestID,
		const FPathFollowingResult& Result
	) override;

	// other properties

};
