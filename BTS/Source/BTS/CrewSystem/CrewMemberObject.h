// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "UObject/NoExportTypes.h"	
#include "PaperSpriteComponent.h"

#include "CrewMemberObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BTS_API UCrewMemberObject : public UObject
{
	GENERATED_BODY()

	UCrewMemberObject();

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayEffect>> MemberEffect;

	UPROPERTY(EditDefaultsOnly)
	FName CrewMemberName;

};
