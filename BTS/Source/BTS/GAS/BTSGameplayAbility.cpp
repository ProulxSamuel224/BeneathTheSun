// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS/GAS/BTSGameplayAbility.h"
#include "AbilitySystemGlobals.h"
#include "BTS/GAS/BTSAbilitySystemComponent.h"

bool UBTSGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bCanActivate = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	bCanActivate &= CheckCanActivate(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	if (!bCanActivate)
	{
		HandleCanActivateFail(OptionalRelevantTags);
	}

	return bCanActivate;
}

bool UBTSGameplayAbility::CheckCanActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	// Custom activation check logic
	return true;
}

bool UBTSGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	UGameplayEffect* CostGE = GetCostGameplayEffect();
	if (CostGE)
	{
		UAbilitySystemComponent* const AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get();
		check(AbilitySystemComponent != nullptr);


		FGameplayEffectSpec	Spec(CostGE, MakeEffectContext(Handle, ActorInfo), GetAbilityLevel(Handle, ActorInfo));
		Spec.CalculateModifierMagnitudes();

		for (int32 ModIdx = 0; ModIdx < Spec.Modifiers.Num(); ++ModIdx)
		{
			const FGameplayModifierInfo& ModDef = Spec.Def->Modifiers[ModIdx];
			const FModifierSpec& ModSpec = Spec.Modifiers[ModIdx];

			// It only makes sense to check additive operators
			if (ModDef.ModifierOp == EGameplayModOp::Additive)
			{
				if (!ModDef.Attribute.IsValid())
				{
					continue;
				}
				const UAttributeSet* Set = AbilitySystemComponent->GetAttributeSet(ModDef.Attribute.GetAttributeSetClass());
				const float CurrentValue = ModDef.Attribute.GetNumericValueChecked(Set);

				// We want to be able to trigger the ability one last time as long as we have some resource left,
				// even if the cost is superior to the current resource value
				if (CurrentValue <= 0.f)
				{
					const FGameplayTag& CostTag = UAbilitySystemGlobals::Get().ActivateFailCostTag;
					if (OptionalRelevantTags && CostTag.IsValid())
					{
						OptionalRelevantTags->AddTag(CostTag);
					}
					return false;
				}
			}
		}
		return true;
	}
	return true;
}

void UBTSGameplayAbility::HandleCanActivateFail(FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!OptionalRelevantTags)
	{
		UE_LOG(LogTemp, Error, TEXT("[GAS] GameplayAbility::HandleCanActivateFail CanActivateAbility failed for unkown reasons."));
	}
	else
	{
		if (OptionalRelevantTags->HasTagExact(UAbilitySystemGlobals::Get().ActivateFailCostTag))
		{
			UE_LOG(LogTemp, Log, TEXT("[GAS] GameplayAbility::HandleCanActivateFail - Not enough resources to activate ability."));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("[GAS] Not enough resources to activate ability."));
		}
		else if (OptionalRelevantTags->HasTagExact(UAbilitySystemGlobals::Get().ActivateFailTagsBlockedTag))
		{
			UE_LOG(LogTemp, Log, TEXT("[GAS] GameplayAbility::HandleCanActivateFail - Activation blocked by another ability."));
		}
	}

	BP_CanActivateAbilityFailed(); // Add fail reason
}


void UBTSGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
	}
}

void UBTSGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}



