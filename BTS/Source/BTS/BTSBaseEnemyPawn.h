// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "BTSBaseEnemyPawn.generated.h"

class UBTSAbilitySystemComponent;

UCLASS()
class BTS_API ABTSBaseEnemyPawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABTSBaseEnemyPawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UShapeComponent* CollisionShape = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", AdvancedDisplay)
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem", AdvancedDisplay)
	UBTSAbilitySystemComponent* AbilitySystemComponent = nullptr;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
