// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Kismet/GameplayStatics.h"
#include "CustomAIController.h"
#include "AnotherCharacterPlayerController.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehTreeTask_RandomPatrol.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API UBehTreeTask_RandomPatrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
private:

	virtual EBTNodeResult::Type ExecuteTask(
		UBehaviorTreeComponent &OwnerComp,
		uint8 *NodeMemory
		) override;

};
