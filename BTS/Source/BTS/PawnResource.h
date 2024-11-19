//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//
//#include "CoreMinimal.h"
//#include "PawnResource.generated.h"
//
//UENUM(BlueprintType)
//enum class EResourceType : uint8 {
//	Health      UMETA(DisplayName = "Health"),
//	Missile     UMETA(DisplayName = "Missiles"),
//	Credits     UMETA(DisplayName = "Credits"),
//};
//
///**
// * 
// */
//UCLASS(ClassGroup = (Custom))
//class BTS_API PawnResource
//{
//	GENERATED_BODY()
//
//public:
//	PawnResource();
//	~PawnResource();
//
//	//Add or decrease current value
//	UFUNCTION(BlueprintCallable)
//	void ChangeCurrentValue(float Value);
//
//	UFUNCTION(BlueprintCallable)
//	void IncreaseMax(float Value);
//
//public:
//	UPROPERTY(EditDefaultsOnly)
//	float InitialValue = 0.0f;
//
//	UPROPERTY(EditDefaultsOnly)
//	float MaxValue = -1.0f;
//
//
//private:
//
//	float CurrentValue = 0.0f;
//};
