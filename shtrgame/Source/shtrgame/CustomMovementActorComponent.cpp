// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMovementActorComponent.h"

// Sets default values for this component's properties
UCustomMovementActorComponent::UCustomMovementActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCustomMovementActorComponent::DriveEvent( float AxisValue ) {

	// reused code from CO2301 lab2

	FVector DeltaLocation = FVector( AxisValue*MoveSpeed*GetWorld()->DeltaTimeSeconds, 0.0f, 0.0f );
	GetOwner()->AddActorLocalOffset( DeltaLocation, true );

}

void UCustomMovementActorComponent::TurnEvent( float AxisValue ) {

	// reused code from CO2301 lab2

	// calc rotation in proper units
	float RotateAmount = AxisValue*RotationSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator( 0.0f, RotateAmount, 0.0f );

	// apply
	GetOwner()->AddActorLocalRotation( FQuat(Rotation), true );

}

void UCustomMovementActorComponent::StrafeEvent( float AxisValue ) {

	FVector DeltaLocation = FVector( 0.0f, AxisValue*MoveSpeed*GetWorld()->DeltaTimeSeconds, 0.0f );
	GetOwner()->AddActorLocalOffset( DeltaLocation, true );

}

/*
// Called when the game starts
void UCustomMovementActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCustomMovementActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

