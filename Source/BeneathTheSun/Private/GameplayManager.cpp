// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayManager.h"
#include "GameplaySettings.h"


void UGameplayManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGameplayManager::Deinitialize()
{
	Super::Deinitialize();
}


void UGameplayManager::SpawnCorridor(const FVector InPosition)
{
	const UGameplaySettings* GameplaySettings = GetDefault<UGameplaySettings>();

	const FVector& Position = InPosition;
	UWorld* World = GetWorld();

	if (IsValid(World))
	{
		const FActorSpawnParameters SpawnParams;
		
		World->SpawnActor<AACorridor>(GameplaySettings->Corridor, Position, FRotator::ZeroRotator, SpawnParams);
	}
}
