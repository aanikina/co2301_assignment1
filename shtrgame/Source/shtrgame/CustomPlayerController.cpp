// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "CustomMovementActorComponent.h"

// reused code from CO2301 lab8

void ACustomPlayerController::BeginPlay() {

    Super::BeginPlay();

    PawnToBeMoved = Cast<AWalkingTeapot>( GetPawn() );

}

void ACustomPlayerController::SetupInputComponent() {

    Super::SetupInputComponent();

	// reused code from CO2301 lab2, lab8

	InputComponent->BindAxis( "Drive", this, &ACustomPlayerController::CallDrive );
	InputComponent->BindAxis( "Turn", this, &ACustomPlayerController::CallTurn );
	InputComponent->BindAxis( "Strafe", this, &ACustomPlayerController::CallStrafe );

}

void ACustomPlayerController::CallDrive( float Value ) {
	
	// foolcheck
	if( !PawnToBeMoved ) { return; }
	
	PawnToBeMoved->CustomMovementActorComp->DriveEvent( Value );
	
}

void ACustomPlayerController::CallStrafe( float Value ) {
	
	// foolcheck
	if( !PawnToBeMoved ) { return; }

	PawnToBeMoved->CustomMovementActorComp->StrafeEvent( Value );
	
}

void ACustomPlayerController::CallTurn( float Value ) {
	
	// foolcheck
	if( !PawnToBeMoved ) { return; }
	
	PawnToBeMoved->CustomMovementActorComp->TurnEvent( Value );

}

