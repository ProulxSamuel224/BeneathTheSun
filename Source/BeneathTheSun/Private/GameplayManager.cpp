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
			AACorridor* NewCorridor= World->SpawnActor<AACorridor>(GameplaySettings->Corridor, SpawnPosition, FRotator::ZeroRotator, SpawnParams);

			if (IsValid(NewCorridor))
			{
				NewCorridor->GetMesh()->SetMaterial(0, NewCorridor->MaterialList[i]);
				GameplayCorridors.Add(NewCorridor);
			}
		}
	}
}


AAProjectile* UGameplayManager::SpawnProjectileOnCorridor(int CorridorIndex, TSubclassOf<AAProjectile> ProjectileToSpawn)
{
	UWorld* World = GetWorld();

	if (IsValid(World))
	{
		if (GetGameplayCorridors().IsValidIndex(CorridorIndex))
		{
			const FActorSpawnParameters SpawnParams;
			AACorridor* Corridor = GameplayCorridors[CorridorIndex];
			AAProjectile* NewProjectile = World->SpawnActor<AAProjectile>(ProjectileToSpawn,Corridor->RuntimeSplineActor->GetActorLocation() , FRotator::ZeroRotator, SpawnParams);

			Corridor->AddActorToCorridor(NewProjectile);
			NewProjectile->SetCurrentCorridorIndex(CorridorIndex);
		}
	}
	return nullptr;
}
