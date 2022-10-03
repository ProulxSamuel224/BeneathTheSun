// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "ACorridor.h"
#include "AProjectile.h"
#include "GameplayManager.generated.h"

/**
 * 
 */
UCLASS()
class BENEATHTHESUN_API UGameplayManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem
	UFUNCTION(BlueprintCallable)
	void SpawnCorridor(const FVector InPosition);

	UFUNCTION(BlueprintCallable)
	void SpawnPlayer(TSubclassOf<AActor> Player);

	UPROPERTY(Transient)
	TArray<AACorridor*> GameplayCorridors;

public:
	UFUNCTION(BlueprintCallable)
	TArray<AACorridor*> GetGameplayCorridors() { return GameplayCorridors; }

	UFUNCTION(BlueprintCallable)
	AAProjectile* SpawnProjectileOnCorridor(int CorridorIndex, TSubclassOf<AAProjectile> ProjectileToSpawn);
};
