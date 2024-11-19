// Fill out your copyright notice in the Description page of Project Settings.


#include "ACorridor.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
AACorridor::AACorridor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void AACorridor::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
	if (IsValid(SplineActor) && IsValid(World))
	{
		const FActorSpawnParameters SpawnParams;
		RuntimeSplineActor = World->SpawnActor<AActor>(SplineActor, GetActorLocation() + SplineOffset, FRotator::ZeroRotator, SpawnParams);

	}
}

// Called every frame
void AACorridor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AACorridor::AddActorToCorridor(AActor* InActor)
{

}

const USplineComponent* AACorridor::GetSplineFromCorridor() const
{
	if (IsValid(RuntimeSplineActor))
	{
		USplineComponent* SplineComp = RuntimeSplineActor->FindComponentByClass<USplineComponent>();
		if (IsValid(SplineComp))
		{
			return SplineComp;
		}

	}
	return nullptr;
}

