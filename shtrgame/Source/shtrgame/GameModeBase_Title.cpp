// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase_Title.h"

void AGameModeBase_Title::BeginPlay() {

    Super::BeginPlay();

	if( TitleWidgetClass ) {
		TitleWidget = CreateWidget(
			UGameplayStatics::GetPlayerController( GetWorld(), 0 ),
			TitleWidgetClass
			);
	}

    StartGame();

}

void AGameModeBase_Title::StartGame() {

	if( TitleWidget ) {
		TitleWidget->AddToViewport();
	}
    
	// set new timer
	GetWorld()->GetTimerManager().SetTimer(
		TitleWaitingTimerHandle,
		this, // which object runs the timer
		&AGameModeBase_Title::TitleWaitingTimerRanOut, // what to do when the timer runs out
		5.0f, // timer duration
		false // loop the timer?
	);

}

void AGameModeBase_Title::TitleWaitingTimerRanOut() {

	// this will allow to set this timer again
	TitleWaitingTimerHandle.Invalidate();

	GameOver( "ActionMap" );

}
		
void AGameModeBase_Title::GameOver( FName LevelName ) {

    UGameplayStatics::OpenLevel( GetWorld(), LevelName );

}
