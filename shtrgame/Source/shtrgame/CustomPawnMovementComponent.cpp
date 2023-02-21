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
	
	// an actor is standing on some plane
	// i want the actor to rotate sideways parallel to this plane
	PawnOwner->AddActorLocalRotation( FRotator( 0.0f, RotateAmount, 0.0f ) );

	// useless anyway
	//PawnOwner->AddControllerYawInput( RotateAmount );

}

void UCustomPawnMovementComponent::LookEvent( float AxisValue ) {

	// help:
	// https://cpp.hotexamples.com/examples/-/-/AddControllerYawInput/cpp-addcontrolleryawinput-function-examples.html
	
	// calc rotation in proper units
	float RotateAmount = AxisValue*RotationSpeed * GetWorld()->DeltaTimeSeconds;

	//ConstrainDirectionToPlane // how???

	// apply
	
	// with current settings it doesn't work
	//PawnOwner->AddControllerPitchInput( RotateAmount );

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

	//--------------------------------+++
	// Definitions.
	
    FHitResult HitResult;
	FVector StartLocation, EndLocation;
	FVector CamSightLineEnd;
	FRotator SecondCameraRotation;

	float RayLength;

	FCollisionQueryParams CollisionParameters;

	//--------------------------------+++
	// Actual code.
	
    RayLength = 2000;

	// i pretend i want to draw a line between camera and something far away at the
	// center of the screen - i start at CameraLocation and arrive at CamSightLineEnd
	SecondCameraRotation = FRotator( CameraRotation.Pitch, CameraRotation.Yaw, CameraRotation.Roll );
	CamSightLineEnd = CameraLocation + ( SecondCameraRotation.Vector() )*RayLength;

	// but actually i want to draw a line between
	StartLocation = CameraLocation;
    EndLocation = CamSightLineEnd;

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

	// reused code from CO2301 lab

	if(TeabagClass) {
	
		// obtain my custom pawn
		// it has projectile spawn point
		AWalkingTeapot *PawnTeapot = Cast<AWalkingTeapot>( PawnOwner );

		FVector SpawnLocation = PawnTeapot->ProjectileSpawnPointSceneComp->GetComponentLocation();
		FRotator SpawnRotation = PawnTeapot->ProjectileSpawnPointSceneComp->GetComponentRotation();
		ATeabag* TempBag = GetWorld()->SpawnActor<ATeabag>( TeabagClass, SpawnLocation, SpawnRotation );

	}

}

void UCustomPawnMovementComponent::DashPressEvent() {
	MoveSpeed += DashSpeed;
}
void UCustomPawnMovementComponent::DashReleaseEvent() {
	MoveSpeed -= DashSpeed;
}