// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "PlayerAttributeSet.h"
#include "ShipAttributeSet.h"
#include "PlayerPawnController.h"
#include "GAS/BTSGameplayAbility.h"

#include "PlayerPawn.generated.h"

class UBTSAbilitySystemComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class BTS_API APlayerPawn : public APawn, public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UShapeComponent* CollisionShape = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", AdvancedDisplay)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Controller", AdvancedDisplay)
	APlayerPawnController* PlayerPawnController = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AbilitySystem",AdvancedDisplay)
	UBTSAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* DefaultMappingContext = nullptr;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveUpAction = nullptr;

	UPROPERTY(EditAnywhere)
	UInputAction* MoveDownAction = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AbilitySystem", AdvancedDisplay)
	UPlayerAttributeSet* PlayerAttributeSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem", AdvancedDisplay)
	UShipAttributeSet* ShipAttributeSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem", AdvancedDisplay)
	TMap<TSubclassOf<UBTSGameplayAbility>, UInputAction*> ActivableAbilities;

	UPROPERTY(EditDefaultsOnly)
	float MoveToSpeed = 0.1f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void MoveUp(const FInputActionValue& Value);
	UFUNCTION()
	void MoveDown(const FInputActionValue& Value);



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


	UFUNCTION(BlueprintCallable)
	const float GetHullAttributeValue();


	UFUNCTION()
	void OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnPawnDied();

	void MoveToLocation(FVector NewLocation);

private:
	void SetAttributeSetChangeDelegates();

	void OnHullChanged(const FOnAttributeChangeData& Data);


private:

	FVector MoveToTargetLocation = FVector::ZeroVector;
	FVector MoveToInitiallocation = FVector::ZeroVector;

	
	
	bool bIsMoving = false;

	float MovementAlpha = 0.f;

};
