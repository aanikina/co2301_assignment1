// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GeneralShell.generated.h"

UCLASS()
class SHTRGAME_API AGeneralShell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralShell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	// reused code from CO2301 lab with teabags
	
	UPROPERTY( VisibleAnywhere )
		UStaticMeshComponent* StaticMeshComp;
	UPROPERTY( VisibleAnywhere )
		UProjectileMovementComponent* ProjectileMovementComp;
		
	// characters can trip on them
	UPROPERTY( EditAnywhere )
		float BaseDamage = 10.0f;
	UPROPERTY( EditAnywhere )
		float FallSpeed = 800.0f;
	UPROPERTY( EditAnywhere )
		float InitialProjectileLifespan = 10.0f; // seconds

	// what will happen when shell falls to the ground
	UFUNCTION()
		void OnHit(
			AActor* SelfActor,
			AActor* OtherActor,
			FVector NormalImpulse,
			const FHitResult& Hit
			);

};
