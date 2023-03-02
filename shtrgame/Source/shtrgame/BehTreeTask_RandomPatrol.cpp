// Fill out your copyright notice in the Description page of Project Settings.


#include "BehTreeTask_RandomPatrol.h"


EBTNodeResult::Type UBehTreeTask_RandomPatrol::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) {

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTTask_Shoot.cpp

	Super::ExecuteTask( OwnerComp, NodeMemory );
	
    //-------------------------+++
    // Preparations.
    
    //UE_LOG( LogTemp, Warning, TEXT("UBehTreeTask_RandomPatrol::TickNode") );

    // i will use Live instead of Player to avoid accidental name
    // clashes

    // get normal and upcasted controllers/pawns of self
    AAIController *BotController = OwnerComp.GetAIOwner();
    ACustomAIController *CustomBotController = Cast<ACustomAIController>( BotController );
    APawn* SelfPawn = BotController->GetPawn();
    APlayerCharacter* CustomSelfPawn = Cast<APlayerCharacter>( SelfPawn );
	
    // make sure i have blackboard
    UBlackboardComponent *SelfBlackboardComp = OwnerComp.GetBlackboardComponent();
    if( !SelfBlackboardComp ) { return EBTNodeResult::Failed; }
    
    // make sure my custom variables are used
    if( !CustomBotController ) { return EBTNodeResult::Failed; }
    if( !CustomSelfPawn ) { return EBTNodeResult::Failed; }
    
    //-------------------------+++
    // Actual code.

    // reused code from CO2301 lab
    
    AActor* Waypoint = CustomBotController->ChooseWaypoint();
    CustomBotController->MoveToActor( Waypoint, 1.0f );

	return EBTNodeResult::Succeeded;

}
