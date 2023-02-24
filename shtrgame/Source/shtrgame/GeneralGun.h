// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneralShell.h"
#include "Kismet/GameplayStatics.h"
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
		
	UFUNCTION()
		void FireTriggerPull();
	UFUNCTION()
		void FireTriggerRelease();
		
	// others should be able to access this class
	// and create it on demand
	UPROPERTY( EditAnywhere )
	    TSubclassOf<UUserWidget> IconWidgetClass;

private:

	UPROPERTY( VisibleAnywhere )
		UStaticMeshComponent* StaticMeshComp;
		
	UPROPERTY( EditAnywhere )
		float BaseDamage = 100.0f;
	UPROPERTY( EditAnywhere )
		float BaseAftershotCooldown = 2.0f; // seconds
		
	UPROPERTY( EditAnywhere )
		USoundBase *FireSound;
		
	UPROPERTY( EditAnywhere )
		TSubclassOf<AGeneralShell> BulletShellClass;

	//UFUNCTION()
		void SpawnBulletShell();
		void SpawnBulletShell( FVector &SpawnLocation, FRotator &SpawnRotation );

};
