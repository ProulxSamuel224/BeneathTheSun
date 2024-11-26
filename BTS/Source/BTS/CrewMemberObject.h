// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "UObject/NoExportTypes.h"
#include "CrewMemberObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BTS_API UCrewMemberObject : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> MemberEffect;

	FName CrewMemberName;

};
