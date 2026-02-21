// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BTS/Combat/CombatTypes.h"
#include "ABaseEnemy.h"
#include "AICoordinator.generated.h"



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

	void GrantAttackToken(AABaseEnemy* Enemy);
	void SetTokenInCooldown(FAttackToken& InToken);
	
	//TimerDelegate
	UFUNCTION()
	void ResetToken(FAttackToken& InToken);

private:
	void HandlePostLoadMap(UWorld* World, const FWorldInitializationValues WorldInitializationValues);

	TArray<TObjectPtr<AABaseEnemy>> SpawnedEnemies;

	TArray<FAttackToken> AvailableAttackTokens;

	TArray<FAttackToken> GrantedAttackTokens;
	
};
