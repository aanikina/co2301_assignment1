// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"
#include "CustomPawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

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
	PawnOwner->AddControllerYawInput( RotateAmount );

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

void UCustomPawnMovementComponent::FireTriggerPullEvent() {
}
void UCustomPawnMovementComponent::FireTriggerReleaseEvent() {
}

void UCustomPawnMovementComponent::DashPressEvent() {
	MoveSpeed += DashSpeed;
}
void UCustomPawnMovementComponent::DashReleaseEvent() {
	MoveSpeed -= DashSpeed;
}