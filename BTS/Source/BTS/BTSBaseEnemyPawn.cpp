// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSBaseEnemyPawn.h"

#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"
#include "BTS/GAS/BTSAbilitySystemComponent.h"
// Sets default values
ABTSBaseEnemyPawn::ABTSBaseEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UBTSAbilitySystemComponent>("AbilitySystemComponent", false);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	CollisionShape = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionShape"));


	RootComponent = CollisionShape;
}

// Called when the game starts or when spawned
void ABTSBaseEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* ABTSBaseEnemyPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called every frame
void ABTSBaseEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABTSBaseEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

