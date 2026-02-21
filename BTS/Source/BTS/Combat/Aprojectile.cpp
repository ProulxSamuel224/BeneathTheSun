// Fill out your copyright notice in the Description page of Project Settings.

#include "AProjectile.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BTS/GameFramework/UGameManager.h"
#include "BTS/Player/PlayerPawn.h"

#include "BTS/AI/ABaseEnemy.h"

// Sets default values
AAProjectile::AAProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	CollisionShape = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionShape"));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	ProjectileMovementComponent->SetUpdatedComponent(CollisionShape);
	/*ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;*/
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	RootComponent = CollisionShape;

	CollisionShape->SetCollisionProfileName(TEXT("Projectile"));

	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionShape->OnComponentHit.AddDynamic(this, &AAProjectile::OnCollisionHit);

	if (GetOwner())
	{
		OwnerPawn = Cast<ABTSBasePawn>(GetOwner());

		if (OwnerPawn)
		{
			OwnerASC = OwnerPawn->GetAbilitySystemComponent();
		}
	}
}

void AAProjectile::InitProjectile()
{
	UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();
	CurrentCorridor = GameManager->GetGameplayCorridors()[CurrentCorridorIndex];

	CurrentCorridorSpline = CurrentCorridor->GetSplineFromCorridor();
}

// Called every frame
void AAProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();
	
	//if (speed < 0.f)
	//{
	//	if(Location.PointsAreNear(Location,CurrentCorridor->GetCorridorStartLocation(),5))
	//	{
	//		Destroy();
	//	}
	//}
	//else
	//{
	//	if (Location.PointsAreNear(Location, CurrentCorridor->GetCorridorEndLocation(), 5))
	//	{
	//		Destroy();
	//	}
	//}
	
	//FHitResult* hit = nullptr;
	//SetActorLocation(CurrentCorridorSpline->GetLocationAtDistanceAlongSpline(DistanceReached, ESplineCoordinateSpace::World), true, hit, ETeleportType::None);

	//DistanceReached += speed;
}

void AAProjectile::OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsValid(OtherActor)&& IsValid(HitDamageEffect))
	{
		if (ABTSBasePawn* HitPawn = Cast<ABTSBasePawn>(OtherActor))
		{
			UAbilitySystemComponent* targetASC = HitPawn->GetAbilitySystemComponent();
			if (targetASC)
			{
				FGameplayEffectSpecHandle DamageSpec =  OwnerASC->MakeOutgoingSpec(HitDamageEffect, 1, OwnerASC->MakeEffectContext());
				UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpec, DamageMagnitudeTag, DamageValue);

				OwnerASC->ApplyGameplayEffectSpecToTarget(*DamageSpec.Data.Get(), targetASC);

				Destroy();
			}
		}
	}
}


void AAProjectile::SetProjectileDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * speed;
}

