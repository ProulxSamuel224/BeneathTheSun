// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EnemyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class BTS_API UEnemyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	/*Piloting*/ //AI Dodge ability
	UPROPERTY()
	FGameplayAttributeData Piloting;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Piloting)

	/*Weapons*/ //AI Damage and Attack Frequency
	UPROPERTY()
	FGameplayAttributeData Weapons;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Weapons)

	/*Shield*/ // AI Defensive and Shield Capabilities
	UPROPERTY()
	FGameplayAttributeData Shielding;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Shielding)
	

	/*Mechanic*/ // AI Repairability and Support effectiveness
	UPROPERTY()
	FGameplayAttributeData Mechanic;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, Mechanic)
};
