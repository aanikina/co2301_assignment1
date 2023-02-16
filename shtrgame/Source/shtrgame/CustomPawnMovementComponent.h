// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CustomPawnMovementComponent.generated.h"

// help:
// https://forums.unrealengine.com/t/addmovementinput-isnt-working-for-me/814/3

UCLASS()
class SHTRGAME_API UCustomPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
		
public:	
	// Sets default values for this component's properties
	UCustomPawnMovementComponent();

	// reused code from CO2301 lab
	
	void DriveEvent( float AxisValue );
	void TurnEvent( float AxisValue );
	void StrafeEvent( float AxisValue );
	void LookEvent( float AxisValue );

	void FireTriggerPullEvent( FVector CameraLocation, FRotator CameraRotation ); //void FireTriggerPullEvent( AActor *ViewTarget );
	void FireTriggerReleaseEvent();
	
	void DashPressEvent();
	void DashReleaseEvent();

protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	UPROPERTY( EditAnywhere )
		float MoveSpeed = 100.0f;
	UPROPERTY( EditAnywhere )
		float RotationSpeed = 100.0f;
	UPROPERTY( EditAnywhere )
		float DashSpeed = 90.0f;
	
};
