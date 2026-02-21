// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "BTS/Base/BTSBasePawn.h"
#include "BTS/Combat/CombatTypes.h"
#include "BTS/GAS/AttributeSets/EnemyAttributeSet.h"
#include "BTS/GAS/AttributeSets/ShipAttributeSet.h"
#include "ABaseEnemy.generated.h"


class UBTSAbilitySystemComponent;

UCLASS()
class BTS_API AABaseEnemy : public ABTSBasePawn
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AABaseEnemy();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//ASC interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//GameplayTag interface
	void AddLooseGameplayTag(FGameplayTag InTag) const;
	void RemoveLooseGameplayTag(FGameplayTag InTag) const;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	UFUNCTION()
	void OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//AI
	void SetAttackToken(FAttackToken inToken) { GrantedAttackToken = inToken; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UShapeComponent* CollisionShape = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", AdvancedDisplay)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem", AdvancedDisplay)
	UEnemyAttributeSet* EnemyAttributeSet = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Transient)
	FAttackToken GrantedAttackToken;

private: 

	void OnHullChanged(const FOnAttributeChangeData& Data);
};
