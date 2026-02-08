// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "BTS/GAS/AttributeSets/ShipAttributeSet.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"

#include "GameFramework/Pawn.h"
#include "BTSBasePawn.generated.h"


class UBTSAbilitySystemComponent;

UCLASS()
class BTS_API ABTSBasePawn : public APawn, public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABTSBasePawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem", AdvancedDisplay)
	UBTSAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem", AdvancedDisplay)
	UShipAttributeSet* ShipAttributeSet = nullptr;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//~ Begin IAbilitySystemInterface
	/** Returns our Ability System Component. */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface
	void AddLooseGameplayTag(FGameplayTag InTag) const;
	void RemoveLooseGameplayTag(FGameplayTag InTag) const;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
