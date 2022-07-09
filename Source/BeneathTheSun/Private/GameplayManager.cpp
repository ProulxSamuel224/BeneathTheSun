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

	UWorld* World = GetWorld();

	if (IsValid(World))
	{
		for (int i = 0; i < GameplaySettings->CorridorAmount; i++)
		{
			
			const FActorSpawnParameters SpawnParams;

			FVector SpawnPosition = InPosition + GameplaySettings->InitialPosition + (GameplaySettings->CorridorOffset*i);
			World->SpawnActor<AACorridor>(GameplaySettings->Corridor, SpawnPosition, FRotator::ZeroRotator, SpawnParams);
		}
	}
}
