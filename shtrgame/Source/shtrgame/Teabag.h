// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Teabag.generated.h"

// reused code from CO2301 lab 3
class UProjectileMovementComponent;

UCLASS()
class SHTRGAME_API ATeabag : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeabag();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY( VisibleAnywhere )
		UStaticMeshComponent* StaticMeshComp;
		
	UPROPERTY( EditAnywhere )
		float MovementSpeed = 1000.0f;
	UPROPERTY( EditAnywhere )
		float BaseDamage = 100.0f;
	UPROPERTY( EditAnywhere )
		float InitialProjectileLifespan = 10.0f;
	
	UPROPERTY( EditAnywhere )
		UProjectileMovementComponent* ProjectileMovementComp;

	UFUNCTION()
		void OnHit(
			AActor* SelfActor,
			AActor* OtherActor,
			FVector NormalImpulse,
			const FHitResult& Hit
			);

};
