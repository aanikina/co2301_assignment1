// Fill out your copyright notice in the Description page of Project Settings.

#include "BehTreeS_HasLineOfSight.h"

/*
void UBehTreeS_HasLineOfSight::OnBecomeRelevant( UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory ) {

    UE_LOG( LogTemp, Warning, TEXT("UBehTreeS_HasLineOfSight::OnBecomeRelevant") );
    //CustomBotController = Cast<ACustomAIController>( GetController() );
    


	if( CustomBotController ) {
		// i want to do some things if this is a ai,
		// not player
		
		// nothing yet

		}

}

void UBehTreeS_HasLineOfSight::OnCeaseRelevant( UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory ) {

    UE_LOG( LogTemp, Warning, TEXT("UBehTreeS_HasLineOfSight::OnCeaseRelevant") );

}
*/

bool UBehTreeS_HasLineOfSight::ICanSeePlayer( APawn *SelfPawn, APawn *LivePawn ) {

	// reused code from CO2301 lab
	
    // vector from this enemy to player
    FVector BetweenThisEnemyAndPlayerVector 
        = LivePawn->GetActorLocation() - SelfPawn->GetActorLocation();
    BetweenThisEnemyAndPlayerVector.Normalize();

    // where is this enemy facing
    FVector ThisEnemyForwardVector = SelfPawn->GetActorForwardVector();
    
    // compute the dot product
    float CosinusBetweenCurrentDirectionAndPlayer = FVector::DotProduct(
        BetweenThisEnemyAndPlayerVector, ThisEnemyForwardVector
    );

    // make sure player is in front of me
    bool bPlayerIsInFrontOfMe = CosinusBetweenCurrentDirectionAndPlayer>=0.0f;
    if( !bPlayerIsInFrontOfMe ) {
        return false;
    }

    //UE_LOG( LogTemp, Warning, TEXT("dot product is: %f"), CosinusBetweenCurrentDirectionAndPlayer );

    return true;

}

void UBehTreeS_HasLineOfSight::TickNode( UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds ) {

	// help:
	// https://github.com/danielpontello/unreal-course-shooter/blob/master/BTService_PlayerLocation.cpp

    Super::TickNode( OwnerComp, NodeMemory, DeltaSeconds );

    //UE_LOG( LogTemp, Warning, TEXT("UBehTreeS_HasLineOfSight::TickNode") );

    // i will use Live instead of Player to avoid accidental name
    // clashes

    // get normal and upcasted controllers
    AAIController *BotController = OwnerComp.GetAIOwner();
    ACustomAIController *CustomBotController = Cast<ACustomAIController>( BotController );
    APlayerController *LiveController = UGameplayStatics::GetPlayerController( GetWorld(), 0 );
    AAnotherCharacterPlayerController *CustomLiveController = Cast<AAnotherCharacterPlayerController>( LiveController );
    
    // get normal and upcasted pawns
    APawn* SelfPawn = BotController->GetPawn();
    APlayerCharacter* CustomSelfPawn = Cast<APlayerCharacter>( SelfPawn );
    APawn* LivePawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 );
    APlayerCharacter* CustomLivePawn = Cast<APlayerCharacter>( LivePawn );
    
    // make sure my custom variables are used
    if( !CustomBotController ) { return; }
    if( !CustomLiveController ) { return; }
    if( !CustomSelfPawn ) { return; }
    if( !CustomLivePawn ) { return; }
    
    // make sure i have blackboard
    UBlackboardComponent *SelfBlackboardComp = OwnerComp.GetBlackboardComponent();
    if( !SelfBlackboardComp ) { return; }

    // make sure i see player
    if( !ICanSeePlayer(SelfPawn,LivePawn) ) { return; }

    // remember things to blackboard

    SelfBlackboardComp->SetValueAsVector( TEXT("PlayerLocation"), LivePawn->GetActorLocation() );

}