// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS/Base/BTSBasePawn.h"

#include "BTS/GAS/BTSAbilitySystemComponent.h"

// Sets default values
ABTSBasePawn::ABTSBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABTSBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABTSBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABTSBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABTSBasePawn::AddLooseGameplayTag(FGameplayTag InTag) const
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddLooseGameplayTag(InTag);
	}
}


void ABTSBasePawn::RemoveLooseGameplayTag(FGameplayTag InTag) const
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(InTag);
	}
}


void ABTSBasePawn::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->GetOwnedGameplayTags(TagContainer);
	}
}


bool ABTSBasePawn::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return AbilitySystemComponent && AbilitySystemComponent->HasMatchingGameplayTag(TagToCheck);
}


bool ABTSBasePawn::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return AbilitySystemComponent && AbilitySystemComponent->HasAllMatchingGameplayTags(TagContainer);
}


bool ABTSBasePawn::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return AbilitySystemComponent && AbilitySystemComponent->HasAnyMatchingGameplayTags(TagContainer);
}

UAbilitySystemComponent* ABTSBasePawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

