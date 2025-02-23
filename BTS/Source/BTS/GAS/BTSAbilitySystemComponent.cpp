// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS/GAS/BTSAbilitySystemComponent.h"


#include "GameplayAbilitySpec.h"
#include "GameplayAbilitySpecHandle.h"
#include "BTS/GAS/BTSGameplayAbility.h"



void UBTSAbilitySystemComponent::InitializeComponent()
{
	GrantInitialAbilities();
	ApplyStartingGameplayEffects();
}


void UBTSAbilitySystemComponent::GiveAbility(TSubclassOf<UBTSGameplayAbility> AbilityClass)
{
	if (!IsValid(AbilityClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("[GAS][Msg] APACThirdPersonCharacterGAS::GiveAbility ability class not properly set. Please check your data."));
		return;
	}

	if (HasAbility(AbilityClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("[GAS][Msg] APACThirdPersonCharacterGAS::GiveAbility character already has ability %s"), *AbilityClass->GetName());
	}


	const FGameplayAbilitySpec AbilitySpec(AbilityClass);
	const FGameplayAbilitySpecHandle Handle = Super::GiveAbility(AbilitySpec);
	GrantedAbilities.Add(AbilityClass, Handle);


	UE_LOG(LogTemp, Log, TEXT("[GAS][Msg] APACThirdPersonCharacterGAS::GiveAbility new ability granted %s"), *AbilityClass->GetName());
}


void UBTSAbilitySystemComponent::RemoveAbility(TSubclassOf<UBTSGameplayAbility> AbilityClass)
{
	const FGameplayAbilitySpecHandle* Handle = GrantedAbilities.Find(AbilityClass);
	if (Handle != nullptr)
	{
		ClearAbility(*Handle);
		GrantedAbilities.Remove(AbilityClass);

		UE_LOG(LogTemp, Log, TEXT("[GAS][Msg] APACThirdPersonCharacterGAS::RemoveAbility ability removed %s"), *AbilityClass->GetName());
		return;
	}


	UE_LOG(LogTemp, Warning, TEXT("[GAS][Msg] APACThirdPersonCharacterGAS::RemoveAbility character doesn't have ability %s"), *AbilityClass->GetName());
}


bool UBTSAbilitySystemComponent::HasAbility(TSubclassOf<UBTSGameplayAbility> AbilityClass)
{
	return GrantedAbilities.Find(AbilityClass) != nullptr;
}

FGameplayAbilitySpecHandle UBTSAbilitySystemComponent::GetGrantedAbilitySpecHandle(TSubclassOf<UBTSGameplayAbility> AbilityClass)
{
	return *GrantedAbilities.Find(AbilityClass);
}


void UBTSAbilitySystemComponent::GrantInitialAbilities()
{
	
	for (TSubclassOf<UBTSGameplayAbility> AbilityClass : StartingAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		FGameplayAbilitySpecHandle Handle = Super::GiveAbility(AbilitySpec);
		GrantedAbilities.Add(AbilityClass, Handle);


		UE_LOG(LogTemp, Log, TEXT("[GAS][Msg] Starting ability granted : %s"), *AbilityClass->GetName());
	}
	
}


void UBTSAbilitySystemComponent::ApplyStartingGameplayEffects()
{
	
	for (const TSubclassOf<UGameplayEffect> EffectClass : StartingGameplayEffect)
	{
		const UGameplayEffect* GameplayEffect = EffectClass->GetDefaultObject<UGameplayEffect>();
		FGameplayEffectContextHandle EffectContext = Super::MakeEffectContext();
		ApplyGameplayEffectToSelf(GameplayEffect, 0, EffectContext);


		UE_LOG(LogTemp, Log, TEXT("[GAS][Msg] Starting gameplay effect applied : %s"), *EffectClass->GetName());
	}
	
}


