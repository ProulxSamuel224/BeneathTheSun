// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	CollisionShape = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionShape"));

	RootComponent = CollisionShape;

	ResourceComponent = CreateDefaultSubobject<UPawnResourceComponent>("ResourceComponent", false);

	PlayerPawnController = CreateDefaultSubobject<APlayerController>("PlayerController", false);

	StaticMesh->SetupAttachment(RootComponent);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent", false);
}

UAbilitySystemComponent* APlayerPawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	CollisionShape->OnComponentHit.AddDynamic(this, &APlayerPawn::OnCollisionHit);

	if (IsValid(ResourceComponent))
	{
		ResourceComponent->OnResourceChangedEvent.AddDynamic(this, &APlayerPawn::OnResourceChanged);
	}
}

void APlayerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(ResourceComponent))
	{
		ResourceComponent->OnResourceChangedEvent.RemoveDynamic(this, &APlayerPawn::OnResourceChanged);
	}
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerPawn::OnResourceChanged(UResourceObject* ResourceChanged)
{
	if (ResourceChanged->ResourceType == EResourceType::Health)
	{
		if (ResourceChanged->GetCurrentValue() <= 0)
		{
			OnPawnDied();
		}
	}
}

void APlayerPawn::OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(2, 10, FColor::Blue, "PlayerPawn Hit");
}

void APlayerPawn::OnPawnDied()
{
	GEngine->AddOnScreenDebugMessage(3, 10, FColor::Blue, "PlayerPawn Dead");
	DisableInput(PlayerPawnController);
}

