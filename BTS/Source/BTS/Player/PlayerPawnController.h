// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPawnController.generated.h"

class APlayerPawn;
/**
 * 
 */

enum class EMovementType : uint8 {
	MoveUp      UMETA(DisplayName = "MoveUp"),
	MoveDown     UMETA(DisplayName = "MoveDown"),

	Count
};


UCLASS()
class BTS_API APlayerPawnController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:
	//UFUNCTION()
	//void MoveUp();
	//UFUNCTION()
	//void MoveDown();

	//UFUNCTION()
	//void TargetUp();
	//UFUNCTION()
	//void TargetDown();

private:

	TObjectPtr<APlayerPawn> PlayerPawn;
};
