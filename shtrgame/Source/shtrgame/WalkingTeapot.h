// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WalkingTeapot.generated.h"

UCLASS()
class SHTRGAME_API AWalkingTeapot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWalkingTeapot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:

	// reused code from CO2301 lab2
	// help:
	// https://docs.unrealengine.com/4.27/en-US/Basics/Components/SkeletalMesh/

	UPROPERTY( VisibleAnywhere )
		USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY( VisibleAnywhere )
		class UCameraComponent* CameraComp;
	UPROPERTY( VisibleAnywhere )
		class USpringArmComponent* CameraSpringArmComp;
	UPROPERTY( VisibleAnywhere )
		class USceneComponent* ProjectileSpawnPointSceneComp;
	UPROPERTY( EditAnywhere )
		float MoveSpeed = 100.0f;
	UPROPERTY( EditAnywhere )
		float RotationSpeed = 100.0f;
	UFUNCTION()
		void MoveByAmount( float Value );
	UFUNCTION()
		void RotateByAmount( float Value );

	FVector DeltaLocation = FVector( 0.0f,0.0f,0.0f );
	FQuat DeltaRotation =  FQuat( 0.0f, 0.0f, 0.0f, 0.0f );

};
