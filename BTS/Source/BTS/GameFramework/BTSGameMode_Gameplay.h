// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "BTS/Player/PlayerPawn.h"
#include "BTSGameMode_Gameplay.generated.h"

/**
 * 
 */
UCLASS()
class BTS_API ABTSGameMode_Gameplay : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPlayerDeath(APlayerPawn* PlayerPawn);

	UFUNCTION(BlueprintCallable)
	void LoadLevel(FName LevelToLoad);


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UUserWidget* GameOverWidgetInstance;
	
};
