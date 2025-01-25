// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BTSGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BTS_API UBTSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:

	//-----------------------------------------------------------------------------------------------------------------------------
	// GameplayAbility function overrides
	//-----------------------------------------------------------------------------------------------------------------------------
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// Please override CheckCanActivate and HandleCanActivateFail instead of this method (probably need a cleaner way to to that) 
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;


	//-----------------------------------------------------------------------------------------------------------------------------
	// Ability activation checks
	//-----------------------------------------------------------------------------------------------------------------------------
	virtual bool CheckCanActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;


	virtual void HandleCanActivateFail(FGameplayTagContainer* OptionalRelevantTags) const;
	UFUNCTION(BlueprintImplementableEvent)
	void BP_CanActivateAbilityFailed(/*TArray<FGameplayTag> RelevantTags*/) const;

	
};
