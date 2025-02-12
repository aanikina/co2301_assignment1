// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Kismet/GameplayStatics.h"
#include "CustomAIController.h"
#include "AnotherCharacterPlayerController.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehTreeS_CheckPlayerStatus.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API UBehTreeS_CheckPlayerStatus : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	// these events never fire for some reason
	// i will handle everything in TickNode(..)
	/*
	// help:
	// https://docs.unrealengine.com/4.27/en-US/API/Developer/AITestSuite/BehaviorTree/UTestBTService_Log/OnBecomeRelevant/
	void OnBecomeRelevant(
		UBehaviorTreeComponent &OwnerComp,
		uint8 *NodeMemory
		);

	void OnCeaseRelevant(
		UBehaviorTreeComponent &OwnerComp,
		uint8 *NodeMemory
		);
	*/

private:
	
	bool PlayerIsInFrontOfMe( APawn *SelfPawn, APawn *LivePawn );

protected:

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTService_PlayerLocationIfSeen.h

	virtual void TickNode(
		UBehaviorTreeComponent &OwnerComp,
		uint8 *NodeMemory,
		float DeltaSeconds ) override;
	
};
