// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AttributeSet.h"

#include "CombatTypes.generated.h"


class AABaseEnemy;

USTRUCT(BlueprintType)
struct FCombatSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinEnemy = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxEnemy = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AABaseEnemy>> enemyEntries;

};

USTRUCT(BlueprintType)
struct FAttackToken
{
	GENERATED_BODY()

	FAttackToken()
	{
		TokenID = GenerateID();
	}

	bool bIsAvailable = true;
	bool bIsGranted = false;
	FTimerHandle CooldownTimerHandle;

private:
	UPROPERTY()
	int32 TokenID;

	static int32 GenerateID()
	{
		static int32 CurrentID = 0;
		return ++CurrentID;
	}

public:
	FORCEINLINE bool operator==(const FAttackToken& Other) const
	{
		return TokenID == Other.TokenID;
	}
};

USTRUCT(BlueprintType)
struct FAttributeBasedCurveValue
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* Curve = nullptr;
	
};

USTRUCT(BlueprintType)
struct FAISettings
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAttributeBasedCurveValue AttackFrequencyCurve;
};
