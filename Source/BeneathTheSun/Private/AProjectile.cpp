// Fill out your copyright notice in the Description page of Project Settings.


#include "AProjectile.h"
#include "GameplayManager.h"

// Sets default values
AAProjectile::AAProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	CollisionShape = CreateDefaultSubobject<UShapeComponent>(TEXT("CollisionShape"));


}

// Called when the game starts or when spawned
void AAProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayManager* GameplayManager = GetGameInstance()->GetSubsystem<UGameplayManager>();
	CurrentCorridor = GameplayManager->GetGameplayCorridors()[CurrentCorridorIndex];
	GEngine->AddOnScreenDebugMessage(0, 10.f, FColor::Red, FString::FromInt(CurrentCorridorIndex),true);
}

// Called every frame
void AAProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

