// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "CustomPawnMovementComponent.h"

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
	InputComponent->BindAxis( "Look", this, &ACustomPlayerController::CallLook );
	
	InputComponent->BindAction( "Fire", IE_Pressed, this, &ACustomPlayerController::CallFireTriggerPull );
	InputComponent->BindAction( "Fire", IE_Released, this, &ACustomPlayerController::CallFireTriggerRelease );
	
	InputComponent->BindAction( "Dash", IE_Pressed, this, &ACustomPlayerController::CallDashPress );
	InputComponent->BindAction( "Dash", IE_Released, this, &ACustomPlayerController::CallDashRelease );

}

void ACustomPlayerController::CallDrive( float Value ) {
	
	// foolcheck
	if( !PawnToBeMoved ) { return; }
	
	PawnToBeMoved->CustomPawnMovementComp->DriveEvent( Value );
	
}

void ACustomPlayerController::CallStrafe( float Value ) {
	
	// foolcheck
	if( !PawnToBeMoved ) { return; }

	PawnToBeMoved->CustomPawnMovementComp->StrafeEvent( Value );
	
}

void ACustomPlayerController::CallTurn( float Value ) {
	
	// foolcheck
	if( !PawnToBeMoved ) { return; }
	
	PawnToBeMoved->CustomPawnMovementComp->TurnEvent( Value );

}

void ACustomPlayerController::CallLook( float Value ) {
	
	// foolcheck
	if( !PawnToBeMoved ) { return; }
	
	PawnToBeMoved->CustomPawnMovementComp->LookEvent( Value );

}

void ACustomPlayerController::CallFireTriggerPull() {
	// foolcheck
	if( !PawnToBeMoved ) { return; }
	PawnToBeMoved->CustomPawnMovementComp->FireTriggerPullEvent();
}
void ACustomPlayerController::CallFireTriggerRelease() {

	// help:
	// https://docs.unrealengine.com/5.1/en-US/API/Runtime/Engine/Kismet/UGameplayStatics/PlaySound2D/
	
	// foolcheck
	if( !PawnToBeMoved ) { return; }

	PawnToBeMoved->CustomPawnMovementComp->FireTriggerReleaseEvent();
	
	/*
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		awawa,
		PawnToBeMoved->GetActorLocation(), //PawnToBeMoved->ProjectileSpawnPointSceneComp->GetComponentLocation(), // reused code from CO2301 lab
		1.0f, // volume
		1.0f, // pitch
		0.0f // delay
	);*/

}

void ACustomPlayerController::CallDashPress() {
	// foolcheck
	if( !PawnToBeMoved ) { return; }
	PawnToBeMoved->CustomPawnMovementComp->DashPressEvent();
}
void ACustomPlayerController::CallDashRelease() {
	// foolcheck
	if( !PawnToBeMoved ) { return; }
	PawnToBeMoved->CustomPawnMovementComp->DashReleaseEvent();
}