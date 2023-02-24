// Fill out your copyright notice in the Description page of Project Settings.


#include "Blueprint/UserWidget.h"
#include "AnotherCharacterPlayerController.h"

AAnotherCharacterPlayerController::AAnotherCharacterPlayerController() {
	
	//Super::APlayerController();


}

void AAnotherCharacterPlayerController::BrieflyShowCurrentGunWidget() {
		
	// help:
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/FTimerHandle/
	if( TimerHandle.IsValid() ) {
		// timer is running, not doing anything
		return;
	}

	SetVisibleCurrentGunWidget( true );

	// reused code from CO2301 lab 7
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this, // which object runs the timer
		&AAnotherCharacterPlayerController::TimerHandleRanOut, // what to do when the timer runs out
		BaseWidgetShowTime, // timer duration
		false // loop the timer?
	);

}

void AAnotherCharacterPlayerController::TimerHandleRanOut() {

	// this will allow to set this timer again
	TimerHandle.Invalidate();
	
	SetVisibleCurrentGunWidget( false );

}

void AAnotherCharacterPlayerController::ChooseCurrentGunWidget() {

	// Forcefully changes CurrentGunWidget.

	// make sure to get rid of already existing
	// if it exists
	if( CurrentGunWidget ) {
		CurrentGunWidget->Destruct();
	}

	// i don't know yet which widget class to show
	TSubclassOf<UUserWidget> WidgetToShowClass;

	// decide which widget class to show
	if( !CurrentGunClass ) {
		// i have no weapon yet
		WidgetToShowClass = GunEmptyWidgetClass;
	}
	else {
		// i have some weapon
		// i need to get actual weapon class instance
		// it is located on the character
		APlayerCharacter *PlayerChar = Cast<APlayerCharacter>( GetPawn() );
		if( PlayerChar ) {
			// i have char, i can get his weapon
			if( PlayerChar->GetCurrentGun() ) { // he has gun
				if( PlayerChar->GetCurrentGun()->IconWidgetClass ) { // it has widget
					WidgetToShowClass = PlayerChar->GetCurrentGun()->IconWidgetClass;
				}
			}
		} // if PlayerChar..
	} // else !CurrentGunClass..

	// make sure i successfully obtained desired widget class
	if( !WidgetToShowClass ) {
		return;
	}
	
	// now i can create the desired widget object
	// but not show it yet
	CurrentGunWidget = CreateWidget( this, WidgetToShowClass );

}

void AAnotherCharacterPlayerController::SetVisibleCurrentGunWidget( bool Visible ) {
	
	if( CurrentGunWidget ) {
		// here i know i already created this widget
	
		// help:
		// https://stackoverflow.com/questions/457577/catching-access-violation-exceptions
		try {
			if( Visible ) {
				// show
				if( !( CurrentGunWidget->IsInViewport() ) ) {
					CurrentGunWidget->AddToViewport( 5 ); // layer 5 just in case
				}
				return;
			}

			// hide
			if( CurrentGunWidget->IsInViewport() ) {
				CurrentGunWidget->RemoveFromViewport();
			}
			return;
		}
		catch( char *e ) {
			// occasionally
			// when i look down and click Fire button
			// widget throws access violation exception
			// i want to ignore such happenings
			UE_LOG( LogTemp, Log, TEXT("access violation while toggling widget in AAnotherCharacterPlayerController::SetVisibleCurrentGunWidget becaues %s"), e );
		}
	}

	// of no, i haven't created this widget yet
	ChooseCurrentGunWidget();
	
	// now i have desired widget object
	// i want to call this function again to show it
	SetVisibleCurrentGunWidget( Visible ); // keep previous option

}

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

}

void AAnotherCharacterPlayerController::InteractPressEvent() {
	
	if( InteractPressSignatureInstance.IsBound() ) {
		InteractPressSignatureInstance.Broadcast(); // Hit.GetActor(), Hit.GetComponent(), Hit.ImpactPoint, Hit.ImpactNormal, Hit.BoneName, Hit );
	}

	UE_LOG( LogTemp, Warning, TEXT("AAnotherCharacterPlayerController::InteractPressEvent") );

}
void AAnotherCharacterPlayerController::InteractReleaseEvent() {

	//UE_LOG( LogTemp, Warning, TEXT("JumpReleaseEvent") );
	
}