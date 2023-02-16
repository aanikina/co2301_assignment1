// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CustomPlayerController.h"
#include "WalkableWall.generated.h"

UCLASS()
class SHTRGAME_API AWalkableWall : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AWalkableWall();
	
	// dont need tick
	//virtual void Tick(float DeltaTime) override; // Called every frame

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	// reused code from CO2301 lab1

	UPROPERTY( VisibleAnywhere )
		UStaticMeshComponent* StaticMeshComp;

	// reused code from CO2301 lab4
	
	UPROPERTY( VisibleAnywhere )
		UBoxComponent* CollisionBoxComp;

	UFUNCTION()
		void OnCollisionBoxOverlapBegin(
			UPrimitiveComponent *OverlappedComp,
			AActor *OtherActor,
			UPrimitiveComponent *OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult
		);

	/*
	UFUNCTION()
		void OnCollisionBoxOverlapEnd(
			UPrimitiveComponent *OverlappedComp,
			AActor *OtherActor,
			UPrimitiveComponent *OtherComp,
			int32 OtherBodyIndex
		);
	*/

};
