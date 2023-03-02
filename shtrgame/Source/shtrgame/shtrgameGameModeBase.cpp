// Copyright Epic Games, Inc. All Rights Reserved.


#include "shtrgameGameModeBase.h"

void AshtrgameGameModeBase::BeginPlay() {

    Super::BeginPlay();

    StartGame();

}

void AshtrgameGameModeBase::StartGame() {

    

}
		
void AshtrgameGameModeBase::GameOver( FName LevelName ) {

    UGameplayStatics::OpenLevel( GetWorld(), LevelName );

}

void AshtrgameGameModeBase::KillScored() {

    HowManyThingsToKill -= 1;

    if( HowManyThingsToKill<=0 ) {
        GameOver( "PlayerSurvivedMap" );
    }

}

void AshtrgameGameModeBase::PlayerDead() {

    GameOver( "PlayerDeadMap" );

}

