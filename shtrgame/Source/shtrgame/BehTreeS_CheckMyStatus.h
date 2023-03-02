// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "Kismet/GameplayStatics.h"
#include "CustomAIController.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehTreeS_CheckMyStatus.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API UBehTreeS_CheckMyStatus : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
protected:

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTService_PlayerLocationIfSeen.h

	virtual void TickNode(
		UBehaviorTreeComponent &OwnerComp,
		uint8 *NodeMemory,
		float DeltaSeconds ) override;
	
};
