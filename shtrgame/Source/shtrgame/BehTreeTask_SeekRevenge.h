// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Kismet/GameplayStatics.h"
#include "CustomAIController.h"
#include "AnotherCharacterPlayerController.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehTreeTask_SeekRevenge.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API UBehTreeTask_SeekRevenge : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTTask_ClearBlackboardValue.h
	
	AActor *GetClosestAttacker( ACustomAIController *CustomBotController, APlayerCharacter* CustomSelfPawn );
	EBTNodeResult::Type RevengeAgainstBot( ACustomAIController *CustomSelfController, APlayerCharacter* CustomSelfPawn, ACustomAIController *CustomAttackerBotController, APlayerCharacter* CustomAttackerPawn );
	EBTNodeResult::Type RevengeAgainstPlayer( ACustomAIController *CustomSelfController, APlayerCharacter* CustomSelfPawn, AAnotherCharacterPlayerController *CustomAttackerLiveController, APlayerCharacter* CustomAttackerPawn );
	EBTNodeResult::Type RevengeAgainstInanimate( AActor* AttackerActor );

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent &OwnerComp,
		uint8 *NodeMemory
		) override;
	
};
