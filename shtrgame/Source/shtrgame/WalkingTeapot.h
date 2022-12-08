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

public:	

	// reused code from CO2301 lab8
	
	UPROPERTY( EditAnywhere )
		class UCustomMovementActorComponent* CustomMovementActorComp;
	
private:

	// reused code from CO2301 lab2
	// help:
	// https://docs.unrealengine.com/4.27/en-US/Basics/Components/SkeletalMesh/

	UPROPERTY( EditAnywhere )
		USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY( EditAnywhere )
		class UCameraComponent* CameraComp;
	UPROPERTY( EditAnywhere )
		class USpringArmComponent* CameraSpringArmComp;
	UPROPERTY( VisibleAnywhere )
		class USceneComponent* ProjectileSpawnPointSceneComp;

};
