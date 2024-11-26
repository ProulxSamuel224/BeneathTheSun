// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

    /*Piloting*/
    UPROPERTY()
    FGameplayAttributeData Piloting;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Piloting)

        /*Weapons*/
    UPROPERTY()
    FGameplayAttributeData Weapons;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Weapons)

        /*Mechanic*/
    UPROPERTY()
    FGameplayAttributeData Mechanic;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Mechanic)
        /*Scouting*/
    UPROPERTY()
    FGameplayAttributeData Scouting;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Scouting)

        /*Science*/
    UPROPERTY()
    FGameplayAttributeData Science;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Science)
        /*Bartering*/
    UPROPERTY()
    FGameplayAttributeData Bartering;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Bartering)
        /*Recruiting*/
    UPROPERTY()
    FGameplayAttributeData Recruiting;
    ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Recruiting)

    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
};
