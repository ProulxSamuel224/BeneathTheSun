// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "ACorridor.h"
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

	UPROPERTY(Transient)
	TArray<AACorridor*> GameplayCorridors;

	UFUNCTION(BlueprintCallable)
	TArray<AACorridor*> GetGameplayCorridors() { return GameplayCorridors; }
};
