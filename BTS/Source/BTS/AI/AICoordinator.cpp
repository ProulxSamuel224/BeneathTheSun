// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS/AI/AICoordinator.h"
#include "BTS/GameplaySettings.h"

void UAICoordinator::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UGameplaySettings* GameplaySettings = GetDefault<UGameplaySettings>();
	const FAttackToken InitToken;
	AvailableAttackTokens.Init(InitToken, GameplaySettings->MaxAIAttackTokens);
}

void UAICoordinator::Deinitialize()
{
	Super::Deinitialize();
}
