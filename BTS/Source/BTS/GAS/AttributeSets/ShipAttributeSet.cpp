// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipAttributeSet.h"

void UShipAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    // Gestion des effets appliqués aux attributs
    //if (Data.EvaluatedData.Attribute == GetHullhAttribute())
    //{
    //    // Exemple : Clamp la santé entre 0 et un maximum défini
    //    Hull.SetCurrentValue(FMath::Clamp(Hull.GetCurrentValue(), 0.0f, 100.0f));
    //}
}