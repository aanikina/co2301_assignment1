// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class SHTRGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	// reused code from CO2301 lab
	
	void DriveEvent( float AxisValue );
	//void TurnEvent( float AxisValue );
	void StrafeEvent( float AxisValue );
	//void LookEvent( float AxisValue );

	void FireTriggerPullEvent( FVector CameraLocation, FRotator CameraRotation ); //void FireTriggerPullEvent( AActor *ViewTarget );
	void FireTriggerReleaseEvent();
	
	void DashPressEvent();
	void DashReleaseEvent();
	void JumpPressEvent();
	void JumpReleaseEvent();
	
	UPROPERTY( EditAnywhere )
		float MoveSpeed = 1000.0f;
	UPROPERTY( EditAnywhere )
		float RotationSpeed = 100.0f;
	UPROPERTY( EditAnywhere )
		float DashSpeed = 1000.0f;
		
	UPROPERTY( VisibleAnywhere )
		class UCameraComponent* CameraComp;
	UPROPERTY( VisibleAnywhere )
		class USpringArmComponent* CameraSpringArmComp;

};
