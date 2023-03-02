// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/UserWidget.h"
#include "AnotherCharacterPlayerController.h"

void AAnotherCharacterPlayerController::SetupInputComponent() {

    Super::SetupInputComponent();
	
	InputComponent->BindAction( "Interact", IE_Pressed, this, &AAnotherCharacterPlayerController::InteractPressEvent );
	//InputComponent->BindAction( "Interact", IE_Released, this, &AAnotherCharacterPlayerController::InteractReleaseEvent );

}

void AAnotherCharacterPlayerController::BeginPlay() {

    Super::BeginPlay();
	
	// reused code from CO2301 lab 9
	
	// i want to create crosshair
	// but don't show it yet
	if( CrosshairWidgetClass ) {
		CrosshairWidget = CreateWidget( this, CrosshairWidgetClass );
	}

}

TSubclassOf<AGeneralGun> AAnotherCharacterPlayerController::GetCurrentGunClass() {

    return CurrentGunClass;

}

void AAnotherCharacterPlayerController::SetVisibleCrosshair( bool SetVisible ) {

	// Shows and hides the interaction prompt.
	
	// make sure i have initialized the prompt
	if( !CrosshairWidget ) {
		// ??? i expect to create it in BeginPlay
		return;
	}

	if( SetVisible ) {
		// show interaction prompt

		if( !( CrosshairWidget->IsInViewport() ) ) {
			CrosshairWidget->AddToViewport();
		}

		return;
	
	}

	// hide interaction prompt

	if( CrosshairWidget->IsInViewport() ) {
		CrosshairWidget->RemoveFromViewport();
	}

}

void AAnotherCharacterPlayerController::SetCurrentGunClass( TSubclassOf<AGeneralGun> NewGunClass ) {

    CurrentGunClass = NewGunClass;
	
	// tell everyone
	if( CurrentGunClasChangedSignatureInstance.IsBound() ) {
		CurrentGunClasChangedSignatureInstance.Broadcast( NewGunClass );
	}

}

void AAnotherCharacterPlayerController::InteractPressEvent() {
	
	if( InteractPressSignatureInstance.IsBound() ) {
		InteractPressSignatureInstance.Broadcast( this );
	}

	//UE_LOG( LogTemp, Warning, TEXT("AAnotherCharacterPlayerController::InteractPressEvent") );

}
void AAnotherCharacterPlayerController::InteractReleaseEvent() {

	UE_LOG( LogTemp, Warning, TEXT("AAnotherCharacterPlayerController::InteractReleaseEvent") );
	
}