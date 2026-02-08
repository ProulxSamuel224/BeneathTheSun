#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"

#include "BTS/Base/BTSBasePawn.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayEffect.h"
#include "BTS/GameFramework/ACorridor.h"
#include "AProjectile.generated.h"


	UCLASS()
		class BTS_API AAProjectile : public AActor
	{
		GENERATED_BODY()

	public:
		// Sets default values for this actor's properties
		AAProjectile();

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float speed = 0.f;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMeshComponent* Mesh = nullptr;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UShapeComponent* CollisionShape = nullptr;

		UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UGameplayEffect> HitDamageEffect;

		UPROPERTY(EditDefaultsOnly)
		FGameplayTag DamageMagnitudeTag = FGameplayTag::EmptyTag;

		UPROPERTY(EditDefaultsOnly)
		float DamageValue = 0.0f;

		UPROPERTY(Transient)
		AACorridor* CurrentCorridor = nullptr;

		UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
		UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

		UPROPERTY(Transient)
		const USplineComponent* CurrentCorridorSpline = nullptr;

		void SetCurrentCorridorIndex(int8 CorridorIndex) { CurrentCorridorIndex = CorridorIndex; }

		int8 CurrentCorridorIndex = 0;

		void InitProjectile();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;


	public:
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		float DistanceReached = 0.f;

		UFUNCTION()
		void OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


		void SetProjectileDirection(const FVector& ShootDirection);


	protected: 

		UPROPERTY(Transient)
		ABTSBasePawn* OwnerPawn = nullptr;

		UPROPERTY(Transient)
		UAbilitySystemComponent* OwnerASC = nullptr;
	};