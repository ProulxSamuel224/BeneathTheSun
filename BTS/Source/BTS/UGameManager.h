// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ACorridor.h"
#include "AProjectile.h"
#include "PlayerPawn.h"
#include "PlayerPawnController.h"

#include "UGameManager.generated.h"

/**
 * 
 */
UCLASS()
class BTS_API UUGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	
	UFUNCTION(BlueprintCallable)
	void SpawnCorridor(const FVector InPosition);


	UFUNCTION(BlueprintCallable)
	void SpawnPlayer(APlayerPawn* Player);

	UPROPERTY(Transient)
	TArray<AACorridor*> GameplayCorridors;

public:
	UFUNCTION(BlueprintCallable)
	TArray<AACorridor*> GetGameplayCorridors() { return GameplayCorridors; }

	UFUNCTION(BlueprintCallable)
	AAProjectile* SpawnProjectileOnCorridor(int CorridorIndex, TSubclassOf<AAProjectile> ProjectileToSpawn);

	UFUNCTION(BlueprintCallable)
	bool DealDamageBetweenActors(UPawnResourceComponent* DamagedTargetComp, UPawnResourceComponent* HitSourceComp);

	void MovePlayerPawnOnCorridor(EMovementType MovementType);

private:

	APlayerPawn* SpawnedPlayer = nullptr;

	uint8 CurrentPlayerCorridorIndex = 0;
};
