// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnotherCharacterPlayerController.h"
#include "GeneralGun.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerCharacter.generated.h"

/*
This Custom Player Character
- is supposed to work with my Custom Player Controller
- is supposed to work with my Custom Enemy AI Controller
*/
UCLASS()
class SHTRGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// i may need to access actual gun instance
	// from somewhere else
	UFUNCTION()
		AGeneralGun *GetCurrentGun();

private:

	// invisible events

	// reused code from CO2301 lab
	
	void DriveEvent( float AxisValue );
	void StrafeEvent( float AxisValue );

	void FireTriggerPullEvent();
	void FireTriggerReleaseEvent();
	
	void DashPressEvent();
	void DashReleaseEvent();
	void JumpPressEvent();
	void JumpReleaseEvent();
	void DrawGunPressEvent();
	void DrawGunReleaseEvent();
		
	// reused code from CO2301 lab 7
	
	void FireCooldownTimerRanOut();
	void DashCooldownTimerRanOut();
	
	FTimerHandle FireCooldownTimerHandle;
	FTimerHandle DashCooldownTimerHandle;

	// invisible properties
		
	UPROPERTY()
		UUserWidget *EmptyHandedWidget;

	// editable properties
	
	UPROPERTY( EditAnywhere )
		float MoveSpeed = 1000.0f;
	UPROPERTY( EditAnywhere )
		float RotationSpeed = 100.0f;
	UPROPERTY( EditAnywhere )
		float DashSpeed = 1000.0f;
	UPROPERTY( EditAnywhere )
		float JumpSpeed = 100.0f;
	UPROPERTY( EditAnywhere )
		float BaseFireCooldownTime = 0.3f; // seconds
	UPROPERTY( EditAnywhere )
		float BaseDashCooldownTime = 1.0f; // seconds
		
	// what to show when i have no gun
	UPROPERTY( EditAnywhere )
	    TSubclassOf<UUserWidget> EmptyHandedWidgetClass;

	// other properties
		
	// i want to be able to manually set necessary gui layer
	// for all relevant widgets
	UPROPERTY( EditAnywhere )
		int GUILayer = 5;

	UPROPERTY( VisibleAnywhere )
		class UCameraComponent* CameraComp;
	UPROPERTY( VisibleAnywhere )
		class USpringArmComponent* CameraSpringArmComp;
		
	// i want to easily see chosen player controller
	UPROPERTY( VisibleAnywhere )
		class AAnotherCharacterPlayerController *CustomPlayerController;
	
	// i want to easily see current gun object instance
	UPROPERTY( VisibleAnywhere )
		AGeneralGun *CurrentGun;

	// ufunctions

	UFUNCTION()
		void DrawCurrentGun();

	UFUNCTION()
		void SetVisibleEmptyHanded( bool SetVisible );
		
	UFUNCTION()
		void BrieflyShowEmptyHanded();
		
	// catch custom signal from player controller
	UFUNCTION()
		void RespondToCurrentGunClasChangedSignatureInstance( TSubclassOf<AGeneralGun> NewGunClass );

};
