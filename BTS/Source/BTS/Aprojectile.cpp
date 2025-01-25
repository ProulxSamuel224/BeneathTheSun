// Fill out your copyright notice in the Description page of Project Settings.


#include "AProjectile.h"
#include "UGameManager.h"
#include "PawnResourceComponent.h"
#include "PlayerPawn.h"

// Sets default values
AAProjectile::AAProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	CollisionShape = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionShape"));

	ResourceComponent = CreateDefaultSubobject<UPawnResourceComponent>("ResourceComponent", false);

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
	if(Location.PointsAreNear(Location,CurrentCorridorSpline->GetLocationAtSplinePoint(CurrentCorridorSpline->GetNumberOfSplinePoints() - 1,ESplineCoordinateSpace::World),5))
	{
		Destroy();
	}
	FHitResult* hit = nullptr;
	SetActorLocation(CurrentCorridorSpline->GetLocationAtDistanceAlongSpline(DistanceReached, ESplineCoordinateSpace::World), true, hit, ETeleportType::None);

	DistanceReached += speed;
}

void AAProjectile::OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (IsValid(OtherActor))
	{
		if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor))
		{
			UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();

			//UResourceObject* Health = PlayerPawn->ResourceComponent->GetResourceByType(EResourceType::Health);
			////GEngine->AddOnScreenDebugMessage(1, 10, FColor::Blue, FString::SanitizeFloat(Health->GetCurrentValue()),false);

			//GameManager->DealDamageBetweenActors(PlayerPawn->ResourceComponent, ResourceComponent);
		//	GEngine->AddOnScreenDebugMessage(2, 10, FColor::Red, FString::SanitizeFloat(Health->GetCurrentValue()),false);
			GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "Projectile Hit",false);

			Destroy();
		}
	}
}

