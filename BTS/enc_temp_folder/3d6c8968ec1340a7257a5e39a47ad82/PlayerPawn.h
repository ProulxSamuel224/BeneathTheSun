// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "PawnResourceComponent.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "PlayerPawn.generated.h"

class UBTSAbilitySystemComponent;

UCLASS()
class BTS_API APlayerPawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UShapeComponent* CollisionShape = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", AdvancedDisplay)
	UStaticMeshComponent* StaticMesh = nullptr;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource", AdvancedDisplay)
	//UPawnResourceComponent* ResourceComponent = nullptr;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Controller", AdvancedDisplay)
	APlayerController* PlayerPawnController = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "AbilitySystem",AdvancedDisplay)
	UBTSAbilitySystemComponent* AbilitySystemComponent = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UBTSAbilitySystemComponent* GetAbilitySystemComponent()  const override;

	//UFUNCTION()
	//void OnResourceChanged(UResourceObject* ResourceChanged);

	UFUNCTION()
	void OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void OnPawnDied();

};
