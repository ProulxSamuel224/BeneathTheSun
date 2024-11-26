// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ShipAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
UCLASS()
class BTS_API UShipAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

    /*Hull*/
    UPROPERTY()
    FGameplayAttributeData Hull;
    ATTRIBUTE_ACCESSORS(UShipAttributeSet, Hull)

    UPROPERTY()
    FGameplayAttributeData MaxHull;
    ATTRIBUTE_ACCESSORS(UShipAttributeSet, MaxHull)

    /*Shield*/
    UPROPERTY()
    FGameplayAttributeData Shield;
    ATTRIBUTE_ACCESSORS(UShipAttributeSet, Shield)

    UPROPERTY()
    FGameplayAttributeData MaxShield;
    ATTRIBUTE_ACCESSORS(UShipAttributeSet, MaxShield)
    
    /*Power*/
    UPROPERTY()
    FGameplayAttributeData Power;
    ATTRIBUTE_ACCESSORS(UShipAttributeSet, Power)
    
    UPROPERTY()
    FGameplayAttributeData MaxPower;
    ATTRIBUTE_ACCESSORS(UShipAttributeSet, MaxPower)
//
    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
};
