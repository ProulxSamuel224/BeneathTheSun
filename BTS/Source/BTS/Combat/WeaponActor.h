// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"

#include "GameplayEffect.h"
#include "WeaponActor.generated.h"

class AAProjectile;
UCLASS()
class BTS_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAProjectile> ProjectileToShoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprite", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> CooldownEffect;


	UPROPERTY(EditDefaultsOnly)
	bool UseTargetting = false;

	UPROPERTY(EditDefaultsOnly)
	FName WeaponName;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool IsWeaponSelected() { return bIsSelected; }

	void SetWeaponSelected(bool InSelected) { bIsSelected = InSelected; }

private:
	bool bIsSelected = false;

};
