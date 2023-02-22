// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneralShell.h"
#include "GeneralGun.generated.h"

UCLASS()
class SHTRGAME_API AGeneralGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneralGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY( VisibleAnywhere )
		class USceneComponent* ShellSpawnPointSceneComp;
		
	//UFUNCTION()
		void SpawnBulletShell();
	//UFUNCTION()
		void SpawnBulletShell( FVector &SpawnLocation, FRotator &SpawnRotation );
		
	UFUNCTION()
		void FireTriggerPull();
	UFUNCTION()
		void FireTriggerRelease();

private:

	UPROPERTY( VisibleAnywhere )
		UStaticMeshComponent* StaticMeshComp;
		
	UPROPERTY( EditAnywhere )
		float BaseDamage = 100.0f;
	UPROPERTY( EditAnywhere )
		float BaseAftershotCooldown = 2.0f; // seconds
		
	UPROPERTY( EditAnywhere )
		TSubclassOf<AGeneralShell> BulletShellClass;

};
