// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS/AI/ABaseEnemy.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"

#include "BTS/GAS/BTSAbilitySystemComponent.h"

// Sets default values
AABaseEnemy::AABaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UBTSAbilitySystemComponent>("AbilitySystemComponent", false);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	CollisionShape = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionShape"));


	RootComponent = CollisionShape;

	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("EnemyAttributes"));
	ShipAttributeSet = CreateDefaultSubobject<UShipAttributeSet>(TEXT("ShipAttributes"));
}

// Called when the game starts or when spawned
void AABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	CollisionShape->OnComponentHit.AddDynamic(this, &AABaseEnemy::OnCollisionHit);




	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AbilitySystemComponent->AddAttributeSetSubobject(EnemyAttributeSet);
		AbilitySystemComponent->AddAttributeSetSubobject(ShipAttributeSet);

		AbilitySystemComponent->InitializeComponent();

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UShipAttributeSet::GetHullAttribute()).AddUObject(this, &AABaseEnemy::OnHullChanged);

	}
	
}

// Called every frame
void AABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABaseEnemy::AddLooseGameplayTag(FGameplayTag InTag) const
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddLooseGameplayTag(InTag);
	}
}


void AABaseEnemy::RemoveLooseGameplayTag(FGameplayTag InTag) const
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(InTag);
	}
}


void AABaseEnemy::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->GetOwnedGameplayTags(TagContainer);
	}
}


bool AABaseEnemy::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return AbilitySystemComponent && AbilitySystemComponent->HasMatchingGameplayTag(TagToCheck);
}


bool AABaseEnemy::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return AbilitySystemComponent && AbilitySystemComponent->HasAllMatchingGameplayTags(TagContainer);
}


bool AABaseEnemy::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return AbilitySystemComponent && AbilitySystemComponent->HasAnyMatchingGameplayTags(TagContainer);
}

UAbilitySystemComponent* AABaseEnemy::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}



void AABaseEnemy::OnCollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(2, 10, FColor::Blue, "Enemy Hit");
}


void AABaseEnemy::OnHullChanged(const FOnAttributeChangeData& Data)
{
	float NewHealth = Data.NewValue;
	float OldHealth = Data.OldValue;

	UE_LOG(LogTemp, Log, TEXT("Health changed from %f to %f"), OldHealth, NewHealth);
	GEngine->AddOnScreenDebugMessage(3, 10, FColor::Green, "Old Health" + FString::SanitizeFloat(OldHealth));
	GEngine->AddOnScreenDebugMessage(4, 10, FColor::Green, "New Health" + FString::SanitizeFloat(NewHealth));

	if (NewHealth <= 0.1f)
	{
		Destroy();
	}

}
