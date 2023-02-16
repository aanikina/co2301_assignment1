// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"
#include "CustomPawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UCustomPawnMovementComponent::UCustomPawnMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCustomPawnMovementComponent::DriveEvent( float AxisValue ) {

	// reused code from CO2301 lab2

	FVector DeltaLocation = FVector( AxisValue*MoveSpeed*GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f );
	GetOwner()->AddActorLocalOffset( DeltaLocation, true );

}

void UCustomPawnMovementComponent::TurnEvent( float AxisValue ) {

	// reused code from CO2301 lab2

	// calc rotation in proper units
	float RotateAmount = AxisValue*RotationSpeed * GetWorld()->DeltaTimeSeconds;

	// apply
	
	//PawnOwner->AddControllerYawInput( RotateAmount );
	
	// an actor is standing on some plane
	// i want the actor to rotate sideways parallel to this plane
	PawnOwner->AddActorLocalRotation( FRotator( 0.0f, RotateAmount, 0.0f ) );

}

void UCustomPawnMovementComponent::LookEvent( float AxisValue ) {

	// help:
	// https://cpp.hotexamples.com/examples/-/-/AddControllerYawInput/cpp-addcontrolleryawinput-function-examples.html
	
	// calc rotation in proper units
	float RotateAmount = AxisValue*RotationSpeed * GetWorld()->DeltaTimeSeconds;

	// apply
	PawnOwner->AddControllerPitchInput( RotateAmount );

}

void UCustomPawnMovementComponent::StrafeEvent( float AxisValue ) {

	FVector DeltaLocation = FVector( 0.0f, AxisValue*MoveSpeed*GetWorld()->DeltaTimeSeconds, 0.0f );
	GetOwner()->AddActorLocalOffset( DeltaLocation, true );

}

void UCustomPawnMovementComponent::FireTriggerPullEvent( FVector CameraLocation, FRotator CameraRotation ) {

	// help:
	// https://www.orfeasel.com/single-line-raycasting/
	// https://cpp.hotexamples.com/examples/-/-/GetActorEyesViewPoint/cpp-getactoreyesviewpoint-function-examples.html
	// https://forums.unrealengine.com/t/how-to-get-active-camera-object/331893/4

	/*
	// reused code from CO2301 lab 3

	if( WalkingTeapotClass ) {


		FVector SpawnLocation = ProjectileSpawnPointSceneComp->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPointSceneComp->GetComponentRotation();
		AATeabag* TempBag = GetWorld()->SpawnActor<AATeabag>( TeabagClass, SpawnLocation, SpawnRotation );

		TempBag->SetOwner( this );
	
	} // if TeabagClass
	//*/

	//--------------------------------+++
	// Definitions.
	
    FHitResult HitResult;
	FVector StartLocation, EndLocation;
	FVector CamSightLineEnd;

	float RayLength;

	FCollisionQueryParams CollisionParameters;

	//--------------------------------+++
	// Actual code.
	
    RayLength = 2000;

	FRotator test;
	
	if( CameraRotation.Pitch<=-30.0f ) {
		test = FRotator( CameraRotation.Pitch+30.0f, CameraRotation.Yaw, CameraRotation.Roll );
	}
	else {
		test = FRotator( CameraRotation.Pitch+5.0f, CameraRotation.Yaw, CameraRotation.Roll );
	}

	// i pretend i want to draw a line between camera and something far away at the
	// center of the screen - i start at CameraLocation and arrive at CamSightLineEnd
	CamSightLineEnd = CameraLocation + ( test.Vector() )*RayLength;

	// but actually i want to draw a line between pawn and CamSightLineEnd
	StartLocation = GetOwner()->GetActorLocation();
    EndLocation = CamSightLineEnd; //ViewTarget->GetActorLocation();
	
	UE_LOG( LogTemp, Warning, TEXT("--- fire") );
	//UE_LOG( LogTemp, Warning, TEXT("start: %s"), *StartLocation.ToString() );
	//UE_LOG( LogTemp, Warning, TEXT("end  : %s"), *EndLocation.ToString() );
	UE_LOG( LogTemp, Warning, TEXT("cam   pitch: %s"), *CameraRotation.ToString() );
	UE_LOG( LogTemp, Warning, TEXT("final pitch: %s"), *test.ToString() );

    GetOwner()->ActorLineTraceSingle(
		HitResult,
		StartLocation, EndLocation,
		ECollisionChannel::ECC_WorldDynamic, CollisionParameters
		);
 
    // boolean parameter forces lines to be persistent so the raycast is not erased in millisecond
    // last parameter is the width of the lines
    DrawDebugLine( GetWorld(), StartLocation, EndLocation, FColor::Orange, true, -1, 0, 1.0f );

}
void UCustomPawnMovementComponent::FireTriggerReleaseEvent() {
}

void UCustomPawnMovementComponent::DashPressEvent() {
	MoveSpeed += DashSpeed;
}
void UCustomPawnMovementComponent::DashReleaseEvent() {
	MoveSpeed -= DashSpeed;
}