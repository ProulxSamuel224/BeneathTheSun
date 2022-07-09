// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ACorridor.h"
#include "GameplaySettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Gameplay Settings"))
class BENEATHTHESUN_API UGameplaySettings : public UDeveloperSettings
{
	GENERATED_BODY()
	

public:


	/* Soft path will be converted to content reference before use */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TSubclassOf<AACorridor> Corridor;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	int32 CorridorAmount = 0;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	float CorridorWidth = 10.0f;
};
