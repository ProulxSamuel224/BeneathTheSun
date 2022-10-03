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

void UGameplayManager::SpawnPlayer(TSubclassOf<AActor> Player)
{
	int8 RandomCorridorIndex = FMath::RandRange(0, GameplayCorridors.Num() - 1);
	if (GameplayCorridors.IsValidIndex(RandomCorridorIndex))
	{
		const AACorridor& SpawnCorridor = *GameplayCorridors[RandomCorridorIndex];

		const USplineComponent& Spline =  *SpawnCorridor.GetSplineFromCorridor();

		FVector SpawnLocation = Spline.GetLocationAtSplinePoint(Spline.GetNumberOfSplinePoints(),ESplineCoordinateSpace::World);

		const FActorSpawnParameters SpawnParams;

		UWorld* World = GetWorld();

		if (IsValid(World))
		{
			AActor* SpawnedPlayer = World->SpawnActor<AActor>(Player, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
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

			NewProjectile->InitProjectile();
		}
	}
	return nullptr;
}
