// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerCapsule.h"
#include "GeneralGun.h"
#include "AnotherCharacterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GunPickupTriggerCapsule.generated.h"

/*
This trigger box:
- displays some gun
- overlaps with any pawn that is controlled by something (a Player or an AI)
- allows my custom Player Controller of the overlapped pawn to pick up the displayed gun
- disappears after being picked up
*/
UCLASS()
class SHTRGAME_API AGunPickupTriggerCapsule : public ATriggerCapsule
{
	GENERATED_BODY()

public:

	AGunPickupTriggerCapsule();

	virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// hidden uproperties
	
	// player is close enough to be able to interact
	UPROPERTY()
	    bool bPlayerIsCloseEnoughToInteract = false;
		
	// i want to spawn this actor in the world
	// so players can see it
	UPROPERTY()
		AGeneralGun *GunActor;
		
	UPROPERTY()
		UUserWidget *InteractPrompt;

	// other uproperties
	
	UPROPERTY( VisibleAnywhere )
		int GUIPromptLayer = 10;
	
	UPROPERTY( EditAnywhere )
		USoundBase *InteractSound;
		
	UPROPERTY( EditAnywhere )
		float IdleRotationSpeed = 30.0f;
	UPROPERTY( EditAnywhere )
		float IdleHoverSpeed = 10.0f;
	UPROPERTY( EditAnywhere )
		float IdleHoverAmplitude = 1.0f;

	// which gun will this pickup point hold
	UPROPERTY( EditAnywhere )
		TSubclassOf<AGeneralGun> GunActorClass;
			
	// choose which prompt is shown when player overlaps with trigger box
	UPROPERTY( EditAnywhere )
	    TSubclassOf<UUserWidget> InteractPromptClass;
		
	// where and how to spawn gun actor
	UPROPERTY( VisibleAnywhere )
		class USceneComponent* GunActorPlacementSceneComp;

	// hidden ufunctions

	// reused code from CO2301 lab4

	UFUNCTION()
		void OnOverlapBegin(
			AActor *OverlappedActor,
			AActor *OtherActor
			);

	UFUNCTION()
		void OnOverlapEnd(
			AActor *OverlappedActor,
			AActor *OtherActor
			);
	
	// catch custom signal from player controller
	UFUNCTION()
		void RespondToInteractSignatureInstancePress( AAnotherCharacterPlayerController *CustomPlayerController );
		
	UFUNCTION()
		void SetVisibleInteractionPrompt( bool SetVisible );
	
	// completely destroys this actor
	UFUNCTION()
		void SelfTerminate();

};
