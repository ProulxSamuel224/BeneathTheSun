// Fill out your copyright notice in the Description page of Project Settings.


#include "AProjectile.h"
#include "UGameManager.h"
#include "PlayerPawn.h"

#include "AI/ABaseEnemy.h"

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
		if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor))
		{
			const UGameplayEffect* GameplayEffect = HitDamageEffect->GetDefaultObject<UGameplayEffect>();
			const FGameplayEffectContextHandle EffectContext = PlayerPawn->GetAbilitySystemComponent()->MakeEffectContext();
			PlayerPawn->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(GameplayEffect, 1.f, EffectContext);

			Destroy();
		}
		if (AABaseEnemy* Enemy = Cast<AABaseEnemy>(OtherActor))
		{
			const UGameplayEffect* GameplayEffect = HitDamageEffect->GetDefaultObject<UGameplayEffect>();
			const FGameplayEffectContextHandle EffectContext = Enemy->GetAbilitySystemComponent()->MakeEffectContext();
			Enemy->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(GameplayEffect, 1.f, EffectContext);

			Destroy();
		}
	}
}


void AAProjectile::SetProjectileDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * speed;
}

