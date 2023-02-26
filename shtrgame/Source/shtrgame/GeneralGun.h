// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneralShell.h"
#include "Kismet/GameplayStatics.h"
#include "GeneralGun.generated.h"

/*
This is a generic Gun. It should be customised via blueprint editor. It can
- do something on fire trigger pull
- spawn a bullet shell on fire trigger pull
- do something on fire trigger release
- have a cooldown / don't have a cooldown between shots
*/
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
	//virtual void Tick(float DeltaTime) override;

	// other properties

	UPROPERTY( VisibleAnywhere )
		class USceneComponent* ShellSpawnPointSceneComp;
		
	// ufunctions

	// i want others to access those
	UFUNCTION()
		bool FireTriggerPull();
	UFUNCTION()
		void FireTriggerRelease();
		
	// others should be able to access this class
	// and create it on demand
	UPROPERTY( EditAnywhere )
	    TSubclassOf<UUserWidget> IconWidgetClass;
		
	UFUNCTION()
		float GetFireCooldown();
	UFUNCTION()
		float GetFireDistance();
	UFUNCTION()
		float GetDamage();

private:

	// other properties

	UPROPERTY( VisibleAnywhere )
		UStaticMeshComponent* StaticMeshComp;

	// editable properties
		
	UPROPERTY( EditAnywhere )
		float BaseDamage = 100.0f;
	UPROPERTY( EditAnywhere )
		float FireCooldown = 1.0f; // seconds
	UPROPERTY( EditAnywhere )
		float FireDistance = 2000.0f; // ray length for raycasting
	UPROPERTY( EditAnywhere )
		USoundBase *FireSound;
	UPROPERTY( EditAnywhere )
		USoundBase *FailedFireSound;
		
	UPROPERTY( EditAnywhere )
		TSubclassOf<AGeneralShell> BulletShellClass;
		
	// invisible functions

	void SpawnBulletShell();
	void SpawnBulletShell( FVector &SpawnLocation, FRotator &SpawnRotation ); // for batch spawning at same location
	
	void FireCooldownTimerRanOut();

	FTimerHandle FireCooldownTimerHandle;

};
