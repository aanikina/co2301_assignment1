// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CustomPlayerCameraManager.generated.h"

// accidentally found mentions of PlayerCameraManager
// in the CustomPlayerController GUI blueprint editor

// help:
// https://unrealcommunity.wiki/player-camera-manager-227ae5
// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Camera/APlayerCameraManager/
// https://forums.unrealengine.com/t/what-is-the-playercameramanager-and-how-could-i-use-it/27296

UCLASS()
class SHTRGAME_API ACustomPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	private:

		void DoUpdateCamera( float DeltaTime );
	
};