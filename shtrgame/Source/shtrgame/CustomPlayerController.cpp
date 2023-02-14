// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "CustomPawnMovementComponent.h"
#include "Blueprint/UserWidget.h"

// reused code from CO2301 lab8

void ACustomPlayerController::BeginPlay() {

    Super::BeginPlay();
	
	// help:
	// https://forums.unrealengine.com/t/gethitresultundercursorforobjects-array/323982/2
	// https://cpp.hotexamples.com/examples/-/-/GetHitResultUnderCursorForObjects/cpp-gethitresultundercursorforobjects-function-examples.html
	//WalkableClasses.Add( AWalkableWall );

    PawnToBeMoved = Cast<AWalkingTeapot>( GetPawn() );
	
	///*
	// reused code from CO2301 lab 9
	
	CrosshairWidget = CreateWidget( this, CrosshairHUDClass );
	if( CrosshairWidget != nullptr ) {
		CrosshairWidget->AddToPlayerScreen();
	}
	//*/


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

	// help:
	// https://docs.unrealengine.com/5.1/en-US/API/Runtime/Engine/GameFramework/APlayerController/GetHitResultUnde-_1/
	// https://forums.unrealengine.com/t/gethitresultundercursorforobjects-array/323982/2

	// foolcheck
	if( !PawnToBeMoved ) { return; }

	/*
    FHitResult HitResult;
	bool bHitOccurred;

	UE_LOG( LogTemp, Warning, TEXT("--- before fire") );
	bHitOccurred = GetHitResultUnderCursorForObjects( WalkableClasses, true, HitResult );
	if(bHitOccurred) {
		//utilize Hit.GetActor() to know who was hit 	
		UE_LOG( LogTemp, Warning, TEXT("hit: %s"), *(HitResult.GetActor()->GetActorLocation()).ToString() );
	}
	//*/
	
	///*
	FVector CameraLocation;
	FRotator CameraRotation;
	GetPlayerViewPoint( CameraLocation, CameraRotation );
	//*/
	
	//PawnToBeMoved->CustomPawnMovementComp->FireTriggerPullEvent( GetViewTarget() );
	//PawnToBeMoved->CustomPawnMovementComp->FireTriggerPullEvent( HitResult.GetActor() );
	PawnToBeMoved->CustomPawnMovementComp->FireTriggerPullEvent( CameraLocation, CameraRotation );

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