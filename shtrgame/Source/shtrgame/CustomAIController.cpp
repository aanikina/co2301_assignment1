// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CustomAIController.h"

ACustomAIController::ACustomAIController() {

    // i don't need tick
    PrimaryActorTick.bCanEverTick = false;

}

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

TSubclassOf<AGeneralGun> ACustomAIController::GetCurrentGunClass() {

    return CurrentGunClass;

}

void ACustomAIController::SetCurrentGunClass( TSubclassOf<AGeneralGun> NewGunClass ) {

    CurrentGunClass = NewGunClass;
	
    /*
	// tell everyone
	if( CurrentGunClasChangedSignatureInstance.IsBound() ) {
		CurrentGunClasChangedSignatureInstance.Broadcast( NewGunClass );
	}*/

}

void ACustomAIController::RemeberThatWasAttackedBy( AActor *AttackerActor ) {

    //UE_LOG( LogTemp, Warning, TEXT("ACustomAIController::RemeberThatWasAttackedBy %s"), AttackerPawn );

    if( WasAttackedBy.Contains( AttackerActor ) ) {
        // this attacker is known
        // TODO
        // raise vendetta meter

        return;

    }

    // this attacker is new
    WasAttackedBy.Add( AttackerActor );

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
    
    GetBlackboardComponent()->ClearValue( TEXT("SelfMovingInProcess") );

    //RandomPatrol();

}

bool ACustomAIController::HasVendettas() {
    
    if( WasAttackedBy.Num()>0 ) {
        return true;
    }
    return false;

}

TArray<AActor*> ACustomAIController::GetAttackers() {
    
    return WasAttackedBy;

}

/*
void ACustomAIController::Tick( float DeltaTime ) {

    Super::Tick( DeltaTime );

}*/
