// Copyright Epic Games, Inc. All Rights Reserved.


#include "shtrgameGameModeBase.h"

void AshtrgameGameModeBase::BeginPlay() {

    Super::BeginPlay();

    StartGame();

}

void AshtrgameGameModeBase::StartGame() {

    

}
		
void AshtrgameGameModeBase::GameOver() {

    UGameplayStatics::OpenLevel( GetWorld(), GameoverLevel );

}

void AshtrgameGameModeBase::KillScored() {

    HowManyThingsToKill -= 1;

    if( HowManyThingsToKill<=0 ) {
		GameoverLevel = "PlayerSurvivedMap";
        GameOver();
    }

}

void AshtrgameGameModeBase::PlayerDead() {

	GameoverLevel = "PlayerDeadMap";
    GameOver();

}

