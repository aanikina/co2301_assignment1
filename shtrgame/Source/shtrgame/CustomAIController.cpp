// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAIController.h"

void ACustomAIController::BeginPlay() {

    Super::BeginPlay();

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 );
    SetFocus( PlayerPawn );

    // remember all the waypoints
    UGameplayStatics::GetAllActorsOfClass( GetWorld(), ATargetPoint::StaticClass(), Waypoints );

}