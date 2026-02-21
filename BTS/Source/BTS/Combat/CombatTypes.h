// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatTypes.generated.h"

USTRUCT(BlueprintType)
struct FAISettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown = 0.f;
};

USTRUCT(BlueprintType)
struct FCombatSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinEnemy = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxEnemy = 5;

};

USTRUCT(BlueprintType)
struct FAttackToken
{
	GENERATED_BODY()

	bool bIsAvailable = true;
	bool bIsGranted = false;
	FTimerHandle CooldownTimerHandle;
};
