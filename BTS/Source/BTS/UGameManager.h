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
	uint8 GetCurrentPlayerCorridorIndex() { return CurrentPlayerCorridorIndex; }
	UFUNCTION(BlueprintCallable)
	uint8 GetCurrentTargettedCorridorIndex() { return CurrentTargettedCorridorIndex; }

	UFUNCTION(BlueprintCallable)
	void SetCurrentTargettedCorridorIndex(uint8 NewCorridorIndex) { CurrentTargettedCorridorIndex = NewCorridorIndex; }

	
	UFUNCTION(BlueprintCallable)
	AAProjectile* SpawnProjectileOnCorridor(int CorridorIndex, TSubclassOf<AAProjectile> ProjectileToSpawn, bool bPlayerProjectile);

	UFUNCTION(BlueprintCallable)

	AAProjectile* ShootProjectile(TSubclassOf<AAProjectile> ProjectileToSpawn, const FVector& SpawnLocation, const FVector& Direction);
	UFUNCTION(BlueprintCallable)
	bool DealDamageBetweenActors(UPawnResourceComponent* DamagedTargetComp, UPawnResourceComponent* HitSourceComp);

	void MovePlayerPawnOnCorridor(EMovementType MovementType);

	void UpdateTargettedCorridor(bool bIsUp);

private:

	APlayerPawn* SpawnedPlayer = nullptr;

	uint8 CurrentPlayerCorridorIndex = 0;
	uint8 CurrentTargettedCorridorIndex = 0;
};
