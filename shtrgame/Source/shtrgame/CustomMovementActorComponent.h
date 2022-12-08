// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomMovementActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHTRGAME_API UCustomMovementActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomMovementActorComponent();

	// reused code from CO2301 lab
	
	void DriveEvent( float AxisValue );
	void TurnEvent( float AxisValue );
	void StrafeEvent( float AxisValue );

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
		
};
