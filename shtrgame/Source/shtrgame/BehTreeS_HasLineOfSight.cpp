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

bool UBehTreeS_HasLineOfSight::PlayerIsInFrontOfMe( APawn *SelfPawn, APawn *LivePawn ) {

    // This function detects that the player's pawn is in front
    // of my enemy pawn. The distance / actual visibility
    // of player pawn are still questionable.

    // If I want to implement stealth mechanics, I will
    // switch from APawn to my custom
    // upcasted pawn.

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
    
    // make sure i have blackboard
    UBlackboardComponent *SelfBlackboardComp = OwnerComp.GetBlackboardComponent();
    if( !SelfBlackboardComp ) { return; }
    
    // make sure my custom variables are used
    if( !CustomBotController ) { return; }
    if( !CustomLiveController ) { return; }
    if( !CustomSelfPawn ) { return; }
    if( !CustomLivePawn ) { return; }

    // remember some things to blackboard
    
    if( CustomBotController->GetCurrentGunClass() ) {
        SelfBlackboardComp->SetValueAsBool( TEXT("SelfHasAGun"), true );
    } else {
        SelfBlackboardComp->SetValueAsBool( TEXT("SelfHasAGun"), false );
    }
    if( CustomSelfPawn->GetCurrentGun() ) {
        SelfBlackboardComp->SetValueAsBool( TEXT("SelfGunIsHidden"), false );
    } else {
        SelfBlackboardComp->SetValueAsBool( TEXT("SelfGunIsHidden"), true );
    }

    // make sure i can see player unobstructed
    bool bIHaveLineOfSight = BotController->LineOfSightTo( LivePawn );
    bool bPlayerIsInFrontOfMe = PlayerIsInFrontOfMe( SelfPawn, LivePawn );

    if( !( bIHaveLineOfSight && bPlayerIsInFrontOfMe ) ) {
        // oh no, something is blocking the player!

        // set appropriate blackboard
        
        // help:
        // https://docs.unrealengine.com/5.1/en-US/BlueprintAPI/AI/Components/Blackboard/ClearValue/
        
        SelfBlackboardComp->ClearValue( TEXT("PlayerLocation") );
        SelfBlackboardComp->ClearValue( TEXT("PlayerHasAGun") );

        return;
    }

    // i can clearly see the player

    SelfBlackboardComp->SetValueAsVector( TEXT("PlayerLocation"), LivePawn->GetActorLocation() );

    // saw player walking around with a gun
    // if the gun is hidden this one should be false
    if( CustomLivePawn->GetCurrentGun() ) {
        SelfBlackboardComp->SetValueAsBool( TEXT("PlayerHasAGun"), true );
    } else {
        SelfBlackboardComp->SetValueAsBool( TEXT("PlayerHasAGun"), false );
    }

}