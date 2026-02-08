// Fill out your copyright notice in the Description page of Project Settings.


#include "UGameManager.h"
#include "GameplaySettings.h"

void UUGameManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUGameManager::Deinitialize()
{
	Super::Deinitialize();
}

void UUGameManager::SpawnCorridor(const FVector InPosition)
{
	const UGameplaySettings* GameplaySettings = GetDefault<UGameplaySettings>();

	UWorld* World = GetWorld();

	if (IsValid(World))
	{
		for (int i = 0; i < GameplaySettings->CorridorAmount; i++)
		{
			const FActorSpawnParameters SpawnParams;

			FVector SpawnPosition = InPosition + GameplaySettings->InitialPosition + (GameplaySettings->CorridorOffset * i);
			AACorridor* NewCorridor = World->SpawnActor<AACorridor>(GameplaySettings->Corridor, SpawnPosition, FRotator::ZeroRotator, SpawnParams);

			if (IsValid(NewCorridor))
			{
				NewCorridor->GetMesh()->SetMaterial(0, NewCorridor->MaterialList[i]);
				GameplayCorridors.Add(NewCorridor);
			}
		}
	}
}

void UUGameManager::SpawnPlayer(APlayerPawn* Player)
{
	int8 RandomCorridorIndex = FMath::RandRange(0, GameplayCorridors.Num() - 1);
	if (GameplayCorridors.IsValidIndex(RandomCorridorIndex))
	{
		 AACorridor* SpawnCorridor = GameplayCorridors[RandomCorridorIndex];

		

		USplineComponent* Spline = SpawnCorridor->GetSplineFromCorridor();

		FVector SpawnLocation = Spline->GetLocationAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::World);

		const FActorSpawnParameters SpawnParams;

		UWorld* World = GetWorld();

		Player->SetActorLocation(SpawnLocation);

		SpawnedPlayer = Player;

		CurrentPlayerCorridorIndex = RandomCorridorIndex;

		CurrentTargettedCorridorIndex = CurrentPlayerCorridorIndex;
		SpawnCorridor->OnCorridorTargetted();

		GEngine->AddOnScreenDebugMessage(1, 10, FColor::Red, "PlayerSpawned");
			
	}
}

AAProjectile* UUGameManager::SpawnProjectileOnCorridor(int CorridorIndex, TSubclassOf<AAProjectile> ProjectileToSpawn,bool bPlayerProjectile)
{
	UWorld* World = GetWorld();

	if (IsValid(World))
	{
		if (GetGameplayCorridors().IsValidIndex(CorridorIndex))
		{
			const FActorSpawnParameters SpawnParams;
			AACorridor* Corridor = GameplayCorridors[CorridorIndex];

			FVector SpawnLocation = Corridor->GetCorridorStartLocation();
			if (bPlayerProjectile)
			{
				SpawnLocation = Corridor->GetCorridorEndLocation();
			}

			AAProjectile* NewProjectile = World->SpawnActor<AAProjectile>(ProjectileToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

			Corridor->AddActorToCorridor(NewProjectile);
			NewProjectile->SetCurrentCorridorIndex(CorridorIndex);

			NewProjectile->InitProjectile();
		}
	}
	return nullptr;
}

AAProjectile* UUGameManager::ShootProjectile(TSubclassOf<AAProjectile> ProjectileToSpawn, const FVector& SpawnLocation, const FVector& Direction, ABTSBasePawn* AbilityOwner)
{
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = AbilityOwner;

	if (IsValid(World))
	{
		AAProjectile* NewProjectile = World->SpawnActor<AAProjectile>(ProjectileToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

		NewProjectile->SetProjectileDirection(Direction);

		return NewProjectile;
	}
	return nullptr;
}

void UUGameManager::MovePlayerPawnOnCorridor(EMovementType MovementType)
{
	GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red,"Test", false);

	if (MovementType == EMovementType::MoveUp)
	{
		if (CurrentPlayerCorridorIndex < (GameplayCorridors.Num() - 1))
		{
			AACorridor* SpawnCorridor = GameplayCorridors[CurrentPlayerCorridorIndex + 1];
			USplineComponent* Spline = SpawnCorridor->GetSplineFromCorridor();

			FVector SpawnLocation = Spline->GetLocationAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::World);

			SpawnedPlayer->MoveToLocation(SpawnLocation);
			CurrentPlayerCorridorIndex++;
		}
	}

	if (MovementType == EMovementType::MoveDown)
	{
		if (CurrentPlayerCorridorIndex > 0)
		{
			AACorridor* SpawnCorridor = GameplayCorridors[CurrentPlayerCorridorIndex -1];
			USplineComponent* Spline = SpawnCorridor->GetSplineFromCorridor();

			FVector SpawnLocation = Spline->GetLocationAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::World);

			SpawnedPlayer->MoveToLocation(SpawnLocation);
			CurrentPlayerCorridorIndex--;
		}
	}
}

void UUGameManager::UpdateTargettedCorridor(bool bIsUp)
{
	if (bIsUp)
	{
		if (CurrentTargettedCorridorIndex < (GameplayCorridors.Num() - 1))
		{
			AACorridor* CurrentTargettedCorridor = GameplayCorridors[CurrentTargettedCorridorIndex];
			CurrentTargettedCorridor->OnCorridorUnTargetted();
			CurrentTargettedCorridorIndex++;
			CurrentTargettedCorridor = GameplayCorridors[CurrentTargettedCorridorIndex];
			CurrentTargettedCorridor->OnCorridorTargetted();
		}
	}
	else
	{
		if (CurrentTargettedCorridorIndex > 0)
		{
			AACorridor* CurrentTargettedCorridor = GameplayCorridors[CurrentTargettedCorridorIndex];
			CurrentTargettedCorridor->OnCorridorUnTargetted();
			CurrentTargettedCorridorIndex--;
			CurrentTargettedCorridor = GameplayCorridors[CurrentTargettedCorridorIndex];
			CurrentTargettedCorridor->OnCorridorTargetted();
		}
	}
}
