// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttributeSet.h"

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    // Gestion des effets appliqu�s aux attributs
    //if (Data.EvaluatedData.Attribute == GetHullhAttribute())
    //{
    //    // Exemple : Clamp la sant� entre 0 et un maximum d�fini
    //    Hull.SetCurrentValue(FMath::Clamp(Hull.GetCurrentValue(), 0.0f, 100.0f));
    //}
}