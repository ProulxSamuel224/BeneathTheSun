// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "ABaseEnemy.h"
#include "AICoordinator.generated.h"

USTRUCT(BlueprintType)
struct FAttackToken
{
	GENERATED_BODY()

	bool bIsAvailable = true;
	bool bIsGranted = false;
	float Cooldown = 0.f;
};

/**
 * 
 */
UCLASS()
class BTS_API UAICoordinator : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	TArray<TObjectPtr<AABaseEnemy>> SpawnedEnemies;

	TArray<FAttackToken> AvailableAttackTokens;

	TArray<FAttackToken> GrantedAttackTokens;
	
};
