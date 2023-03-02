// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase_Title.generated.h"

/**
 * 
 */
UCLASS()
class SHTRGAME_API AGameModeBase_Title : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
private:

	void TitleWaitingTimerRanOut();

	FTimerHandle TitleWaitingTimerHandle;

	UPROPERTY( EditAnywhere )
	    TSubclassOf<UUserWidget> TitleWidgetClass;
	UPROPERTY()
		UUserWidget *TitleWidget;

	UFUNCTION()
		void StartGame();
		
	UFUNCTION()
		void GameOver( FName LevelName );

};
