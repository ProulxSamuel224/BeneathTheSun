// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class BTS_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
    /*Piloting*/ // Switch trajectory speed, dodge and speed
    UPROPERTY()
    FGameplayAttributeData Piloting;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Piloting)

    /*Weapons*/ // Damage and attack cooldown 
    UPROPERTY() 
    FGameplayAttributeData Weapons;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Weapons)

    /*Shield*/ //Defensive ahd Shield Capabilities ( Regen/ Max Shield
    UPROPERTY()
    FGameplayAttributeData Shielding;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Shielding)

	/*Mechanic*/ //Repairabilility and Support effectiveness ( Repair Speed, Buff Strength)
    UPROPERTY()
    FGameplayAttributeData Mechanic;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Mechanic)
    
    /*Scouting*/ //Effectiveness of scouting, seeing incoming events, choice and enemies
    UPROPERTY()
    FGameplayAttributeData Scouting;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Scouting)

    /*Science*/ // Dictates energy levels, item quality in shops
    UPROPERTY()
    FGameplayAttributeData Science;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Science)
    
    /*Bartering*/ // Dictates max credits capacity + lowering Shop Prices
    UPROPERTY()
    FGameplayAttributeData Bartering;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Bartering)
    
    /*Recruiting*/ // Dictates the quality of crew stats and maximum crew members
    UPROPERTY()
    FGameplayAttributeData Recruiting;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Recruiting)

    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
};