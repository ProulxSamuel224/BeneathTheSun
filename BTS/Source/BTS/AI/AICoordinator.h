// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BTS/Combat/CombatTypes.h"
#include "ABaseEnemy.h"
#include "AICoordinator.generated.h"

class AACorridor;

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

	UFUNCTION()
	void GrantAttackToken(AABaseEnemy* Enemy);
	void SetTokenInCooldown(FAttackToken& InToken);
	void HandleCombatStart(FCombatSettings CombatSettings, const TArray<AACorridor*>& GameplayCorridors);
	
	//TimerDelegate
	UFUNCTION()
	void ResetToken(FAttackToken& InToken);
	void StartTokenGranting();

private:
	void HandlePostLoadMap(UWorld* World, const FWorldInitializationValues WorldInitializationValues);

	void OnGrantedTokenConsumed(AABaseEnemy* Enemy);
	void OnEnemyDeath(AABaseEnemy* Enemy);

	TMap<AABaseEnemy*,FAttackToken> SpawnedEnemies;

	FTimerHandle GrantTokenTimerHandle;
	
};
