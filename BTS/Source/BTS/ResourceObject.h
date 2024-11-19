// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ResourceObject.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EResourceType : uint8 {
	Health      UMETA(DisplayName = "HealthPoints"),
	Missile     UMETA(DisplayName = "Missiles"),
	Credits     UMETA(DisplayName = "Credits"),
	Damage      UMETA(DisplayName = "DamagePoints"),

	Count
 };

UCLASS(BlueprintType,Blueprintable,DefaultToInstanced,EditInlineNew)
class BTS_API UResourceObject : public UObject
{
	GENERATED_BODY()
	

public:
    
    UFUNCTION(BlueprintCallable)
	void ChangeCurrentValue(float Value);

    UFUNCTION(BlueprintCallable)
	void ChangeMaxValue(float Value);

	UFUNCTION(BlueprintCallable)
	float GetCurrentValue() { return CurrentValue; }

	void InitResource();

public:

    UPROPERTY(EditDefaultsOnly)
	float InitialValue = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxValue = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	EResourceType ResourceType = EResourceType::Count;

private:

	float CurrentValue = 0.0f;

	float CurrentMaxValue = 0.0f;

};
