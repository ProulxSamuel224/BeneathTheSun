// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BTSAbilitySystemComponent.generated.h"

class UBTSGameplayAbility;
/**
 * 
 */
UCLASS()
class BTS_API UBTSAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public :

	void InitializeComponent();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GiveAbility(TSubclassOf<UBTSGameplayAbility> AbilityClass);


	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void RemoveAbility(TSubclassOf<UBTSGameplayAbility> AbilityClass);


	UFUNCTION(BlueprintCallable, Category = "Abilities")
	bool HasAbility(TSubclassOf<UBTSGameplayAbility> AbilityClass);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	FGameplayAbilitySpecHandle GetGrantedAbilitySpecHandle(TSubclassOf<UBTSGameplayAbility> AbilityClass);


private:
	void GrantInitialAbilities();


	// List of abilities to be granted on BeginPlay
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UBTSGameplayAbility>> StartingAbilities;


	TMap<TSubclassOf<UBTSGameplayAbility>, FGameplayAbilitySpecHandle> GrantedAbilities = {};

	//-----------------------------------------------------------------------------------------------------------------------------
	// Gameplay Effects
	//-----------------------------------------------------------------------------------------------------------------------------
private:
	void ApplyStartingGameplayEffects();

	// List of GameplayEffect to be applied on BeginPlay
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartingGameplayEffect;

	
};
