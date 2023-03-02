// Fill out your copyright notice in the Description page of Project Settings.


#include "BehTreeS_CheckMyStatus.h"

void UBehTreeS_CheckMyStatus::TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) {

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTService_PlayerLocation.cpp

    Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );

    //-------------------------+++
    // Preparations.

    // get normal and upcasted controllers
    AAIController *BotController = OwnerComp.GetAIOwner();
    ACustomAIController *CustomBotController = Cast<ACustomAIController>( BotController );
    
    // get normal and upcasted pawns
    APawn* SelfPawn = BotController->GetPawn();
    APlayerCharacter* CustomSelfPawn = Cast<APlayerCharacter>( SelfPawn );
    
    // make sure i have blackboard
    UBlackboardComponent *SelfBlackboardComp = OwnerComp.GetBlackboardComponent();
    if( !SelfBlackboardComp ) { return; }
    
    // make sure my custom variables are used
    if( !CustomBotController ) { return; }
    if( !CustomSelfPawn ) { return; }
    
    //-------------------------+++
    // Actual code.

    // remember some things to blackboard
    
    // do i have a gun?
    if( CustomBotController->GetCurrentGunClass() ) {
        SelfBlackboardComp->SetValueAsBool( TEXT("SelfHasAGun"), true );
    } else {
        SelfBlackboardComp->SetValueAsBool( TEXT("SelfHasAGun"), false );
    }

    // is it hidden from player?
    if( CustomSelfPawn->GetCurrentGun() ) {
        SelfBlackboardComp->SetValueAsBool( TEXT("SelfGunIsHidden"), false );
    } else {
        SelfBlackboardComp->SetValueAsBool( TEXT("SelfGunIsHidden"), true );
    }

}
