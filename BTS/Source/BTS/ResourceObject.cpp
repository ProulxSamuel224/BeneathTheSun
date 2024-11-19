// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceObject.h"

void UResourceObject::ChangeCurrentValue(float Value)
{
	CurrentValue = FMath::Clamp(CurrentValue += Value, 0, CurrentMaxValue);
}

void UResourceObject::ChangeMaxValue(float Value)
{
	CurrentMaxValue += Value;
}

void UResourceObject::InitResource()
{
	CurrentMaxValue = MaxValue;
	CurrentValue = FMath::Clamp(InitialValue,0, MaxValue);
}
