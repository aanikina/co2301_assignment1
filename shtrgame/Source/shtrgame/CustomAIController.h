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

public:

	ACustomAIController();

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
	UPROPERTY()
		TArray<AActor*> WasAttackedBy;

	// editable properties
	
	UPROPERTY( EditAnywhere )
		UBehaviorTree* EnemyBehaviorTree;

	void RandomPatrol();

public:
	
	// functions

	void Tick( float DeltaTime ) override;

	// functions
	
	// help:
	// https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/GameplayArchitecture/Functions/
	UFUNCTION( BlueprintCallable )
		AActor* ChooseWaypoint();

	void OnMoveCompleted(
		FAIRequestID RequestID,
		const FPathFollowingResult& Result
	) override;
	
	// allow others to access player's gun settings
	UFUNCTION()
		TSubclassOf<AGeneralGun> GetCurrentGunClass();
	UFUNCTION()
		void SetCurrentGunClass( TSubclassOf<AGeneralGun> NewGunClass );
	
	UFUNCTION()
		void RemeberThatWasAttackedBy( AActor *AttackerActor );
		
	UFUNCTION()
		bool HasVendettas();
		
	UFUNCTION()
		TArray<AActor*> GetAttackers();

};
