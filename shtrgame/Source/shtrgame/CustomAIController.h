// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomAIController.generated.h"


// i want enemies to behave differently based on their mood
// mood can change depending on hp / other factors

// in this file i have:
// - c++ enum definition CppMoodWhimEnum
// - public variable CurrentMoodWhim that will hold CppMoodWhimEnum value;

// in the unreal engine i have:
// - .uasset enum definition BlueprintMoodWhimEnum
// - Blackboard Key SelfMoodWhim that will hold BlueprintMoodWhimEnum

// in this file (corresponding .cpp) i will
// - change CurrentMoodWhim
// - set blackboard key SelfMoodWhim using CppMoodWhimEnum

// in the unreal engine behaviour tree i will
// - read the value of SelfMoodWhim using BlueprintMoodWhimEnum
// - call some behaviour tree services that will use CppMoodWhimEnum

// i do all this because i don't know how to access
// .uasset BlueprintMoodWhimEnum values from this file
// i expect CppMoodWhimEnum and BlueprintMoodWhimEnum
// to be identical

// help:
// https://forums.unrealengine.com/t/creating-enums-in-c/465555/2
// https://www.oreilly.com/library/view/unreal-engine-4/9781785885549/ch02s10.html
// https://forums.unrealengine.com/t/uenum-inside-of-class-enum-is-not-allowed-here/359498/4
// i get error "enum is not allowed here" when i place it inside the class
// so i put it here
// also when i comment it out unreal engine fails to
// compile the project (says it can't parse header)
///*
UENUM( BlueprintType )
	enum CppMoodWhimEnum { //enum class BehaviorMoodWhim : uint8 {
		Neutral UMETA( DisplayName="NeutralPassive" ), // no attack (default)
		Berserk UMETA( DisplayName="BerserkOffensive" ), // kill everyone
		Predator UMETA( DisplayName="PredatorOffensive" ), // kill defenceless
		Officer UMETA( DisplayName="OfficerOffensive" ), // kill armed
		Panic UMETA( DisplayName="PanicDefensive" ) // run away from everyone
		};
		//*/

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
	
	// help:
	// https://forums.unrealengine.com/t/creating-enums-in-c/465555/2
	// https://www.oreilly.com/library/view/unreal-engine-4/9781785885549/ch02s10.html
	// compiler says it has to be public
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
		TEnumAsByte<CppMoodWhimEnum> CurrentMoodWhim; // apparently value 0 is selected by default

};
