// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/UserWidget.h"
#include "AnotherCharacterPlayerController.h"

void AAnotherCharacterPlayerController::SetupInputComponent() {

    Super::SetupInputComponent();
	
	InputComponent->BindAction( "Interact", IE_Pressed, this, &AAnotherCharacterPlayerController::InteractPressEvent );
	//InputComponent->BindAction( "Interact", IE_Released, this, &AAnotherCharacterPlayerController::InteractReleaseEvent );

}

TSubclassOf<AGeneralGun> AAnotherCharacterPlayerController::GetCurrentGunClass() {

    return CurrentGunClass;

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