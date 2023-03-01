// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CustomAIController.h"

void ACustomAIController::BeginPlay() {

    Super::BeginPlay();

	// reused code from CO2301 lab 11

    // remember all the waypoints
    UGameplayStatics::GetAllActorsOfClass( GetWorld(), ATargetPoint::StaticClass(), Waypoints );
    
    if( EnemyBehaviorTree ) {
        RunBehaviorTree( EnemyBehaviorTree );
    }
    
    // fill blackboard
    if( GetBlackboardComponent() ) {

        GetBlackboardComponent()->SetValueAsVector( TEXT("StartLocation"), GetPawn()->GetActorLocation() );

    }

}

AActor* ACustomAIController::ChooseWaypoint() {

    int iloc = FMath::RandRange( 0, Waypoints.Num()-1 );
    return Waypoints[iloc];

}

void ACustomAIController::RandomPatrol() {

    MoveToActor( ChooseWaypoint() );

}

void ACustomAIController::OnMoveCompleted( FAIRequestID RequestID, const FPathFollowingResult &Result ) {
    
    Super::OnMoveCompleted( RequestID, Result );

    //RandomPatrol();

}

void ACustomAIController::Tick( float DeltaTime ) {

    Super::Tick( DeltaTime );
    
    // necessary pawns
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 );
    APawn* ThisEnemyPawn = GetPawn();
    
    if( GetBlackboardComponent() ) {
        // remember player location to blackboard
        GetBlackboardComponent()->SetValueAsVector( TEXT("PlayerLocation"), PlayerPawn->GetActorLocation() );
    }
    
    // vector from this enemy to player
    FVector BetweenThisEnemyAndPlayerVector 
        = PlayerPawn->GetActorLocation() - ThisEnemyPawn->GetActorLocation();
    BetweenThisEnemyAndPlayerVector.Normalize();
    
    // where is this enemy facing
    FVector ThisEnemyForwardVector = ThisEnemyPawn->GetActorForwardVector();
    
    // compute the dot product
    float CosinusBetweenCurrentDirectionAndPlayer = FVector::DotProduct(
        BetweenThisEnemyAndPlayerVector, ThisEnemyForwardVector
    );
    //UE_LOG( LogTemp, Warning, TEXT("dot product is: %f"), CosinusBetweenCurrentDirectionAndPlayer );

}
