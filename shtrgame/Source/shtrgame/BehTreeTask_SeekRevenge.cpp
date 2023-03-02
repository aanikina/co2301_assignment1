// Fill out your copyright notice in the Description page of Project Settings.


#include "BehTreeTask_SeekRevenge.h"

AActor* UBehTreeTask_SeekRevenge::GetClosestAttacker( ACustomAIController *CustomBotController, APlayerCharacter* CustomSelfPawn ) {

    // TODO
    // check if they are reachable?

    TArray<AActor*> AttackerActors = CustomBotController->GetAttackers();
    AActor *ClosestAttacker = nullptr;

    FVector MyLocation = CustomSelfPawn->GetActorLocation();

    // iterate all attackers
    // this one fails:
    //for( APawn* AttackerPawn : AttackerPawns ) {
    for( int iloc=0; iloc<AttackerActors.Num(); iloc+=1 ) {

        if( !ClosestAttacker ) {
            // set first one
            ClosestAttacker = AttackerActors[iloc];
        }

        // compare distance
        // help:
        // https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Math/FVector/
        float ToPawn = ( MyLocation - AttackerActors[iloc]->GetActorLocation() ).Size();
        float ToClosest = ( MyLocation - ClosestAttacker->GetActorLocation() ).Size();

        if( ToPawn < ToClosest ) {
            ClosestAttacker = AttackerActors[iloc];
        }
        
    } // for AttackerPawn..

    return ClosestAttacker;

}

EBTNodeResult::Type UBehTreeTask_SeekRevenge::RevengeAgainstBot(
    ACustomAIController *CustomSelfController,
    APlayerCharacter* CustomSelfPawn,
    ACustomAIController *CustomAttackerBotController,
    APlayerCharacter* CustomAttackerPawn ) {

	//UE_LOG( LogTemp, Warning, TEXT("UBehTreeTask_SeekRevenge::RevengeAgainstBot") );

    CustomSelfController->MoveToActor( CustomAttackerPawn, 5.0f );
    
    return EBTNodeResult::Succeeded;

}

EBTNodeResult::Type UBehTreeTask_SeekRevenge::RevengeAgainstPlayer(
    AAnotherCharacterPlayerController *CustomAttackerLiveController,
    APlayerCharacter* CustomAttackerPawn ) {

	UE_LOG( LogTemp, Warning, TEXT("UBehTreeTask_SeekRevenge::RevengeAgainstPlayer") );
    
    return EBTNodeResult::Succeeded;

}

EBTNodeResult::Type UBehTreeTask_SeekRevenge::RevengeAgainstInanimate(
    AActor* AttackerActor ) {

	UE_LOG( LogTemp, Warning, TEXT("UBehTreeTask_SeekRevenge::RevengeAgainstInanimate") );

    // TODO
    // allow to kick actor and randomly fail
    // also injuring self

    return EBTNodeResult::Succeeded;

}

EBTNodeResult::Type UBehTreeTask_SeekRevenge::ExecuteTask( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory ) {

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTTask_Shoot.cpp

	Super::ExecuteTask( OwnerComp, NodeMemory );
	
    //-------------------------+++
    // Preparations.
    
    //UE_LOG( LogTemp, Warning, TEXT("UBehTreeS_CheckPlayerStatus::TickNode") );

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

    // whom i have vendettas against? i know i have them because selectors
    // find the closest one
    
    AActor *ClosestAttacker = GetClosestAttacker( CustomBotController, CustomSelfPawn );
    
    //-------------------------+++
    // Actual code.

    if( !ClosestAttacker ) {
        // all attackers are unreachable
        // TODO
        // set blackboard key to study a blade or something
	    return EBTNodeResult::Succeeded;
    }
    
    // this attacker is reachable
    
	//UE_LOG( LogTemp, Warning, TEXT("found closest attacker %s"), ClosestAttacker );

    // attempt to get various normal and upcasted
    // controllers/pawns of attacker

    APlayerCharacter* CustomAttackerPawn = Cast<APlayerCharacter>( ClosestAttacker );

    if( !CustomAttackerPawn ) {
        // i was attacked not by my custom character
        return RevengeAgainstInanimate( ClosestAttacker );
    }

    // i was attacked by my custom character, but who controls it?
    
    ACustomAIController *CustomAttackerBotController = Cast<ACustomAIController>( CustomAttackerPawn->GetController() );
    AAnotherCharacterPlayerController *CustomAttackerLiveController = Cast<AAnotherCharacterPlayerController>( CustomAttackerPawn->GetController() );
    
    if( CustomAttackerLiveController ) {
        // even though i see CustomAttackerLiveController
        // through the debugger,
        // i always end up in the next branch
        return RevengeAgainstPlayer( CustomAttackerLiveController, CustomAttackerPawn );
    } else if( CustomAttackerBotController ) {
        // i end up here even with CustomAttackerLiveController
        

        SelfBlackboardComp->SetValueAsVector( TEXT("LastAttackerPosition"), CustomAttackerPawn->GetActorLocation() );
        return RevengeAgainstBot( CustomBotController, CustomSelfPawn, CustomAttackerBotController, CustomAttackerPawn );
        
        //OwnerComp.GetAIOwner()->MoveToActor( CustomAttackerPawn, 5.0f );
        //return EBTNodeResult::Succeeded;

    }
    
	UE_LOG( LogTemp, Warning, TEXT("my closest attacker is controlled by something unknown, can't take revenge") );

	return EBTNodeResult::Failed;

}
