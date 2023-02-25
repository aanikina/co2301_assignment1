// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API ACustomAIController : public AAIController
{
	GENERATED_BODY()

/*
protected:

	virtual void BeginPlay() override;
	
private:

	// reused code from CO2301 lab 11

	UPROPERTY()
		TArray<AActor*> Waypoints;
	
	UPROPERTY(EditAnywhere)
		UBehaviorTree* EnemyBehaviorTree;
		
	AActor* ChooseWaypoint();
	void RandomPatrol();

public:
	
	void Tick( float DeltaTime ) override;

	void OnMoveCompleted(
		FAIRequestID RequestID,
		const FPathFollowingResult& Result
	) override;
*/

};
