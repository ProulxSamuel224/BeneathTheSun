// Fill out your copyright notice in the Description page of Project Settings.


#include "AProjectile.h"
#include "GameplayManager.h"

// Sets default values
AAProjectile::AAProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	CollisionShape = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionShape"));

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
	UGameplayManager* GameplayManager = GetGameInstance()->GetSubsystem<UGameplayManager>();
	CurrentCorridor = GameplayManager->GetGameplayCorridors()[CurrentCorridorIndex];
	
	CurrentCorridorSpline = CurrentCorridor->GetSplineFromCorridor();

}

// Called every frame
void AAProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult* hit = nullptr;
	SetActorLocation(CurrentCorridorSpline->GetLocationAtDistanceAlongSpline(DistanceReached,ESplineCoordinateSpace::World),true,hit,ETeleportType::None);

	DistanceReached += speed;

}

void AAProjectile::OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

