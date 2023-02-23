// Fill out your copyright notice in the Description page of Project Settings.


#include "AnotherCharacterPlayerController.h"

TSubclassOf<AGeneralGun> AAnotherCharacterPlayerController::GetCurrentGunClass() {

    return CurrentGunClass;

}

void AAnotherCharacterPlayerController::SetCurrentGunClass( TSubclassOf<AGeneralGun> NewGunClass ) {

    CurrentGunClass = NewGunClass;

}