// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS/AI/AICoordinator.h"
#include "BTS/GameFramework/GameplaySettings.h"

void UAICoordinator::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UGameplaySettings* GameplaySettings = GetDefault<UGameplaySettings>();

	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UAICoordinator::HandlePostLoadMap);
}

void UAICoordinator::Deinitialize()
{
	GrantTokenTimerHandle.Invalidate();
	Super::Deinitialize();
}

void UAICoordinator::GrantAttackToken(AABaseEnemy* Enemy)
{
	FAttackToken& token = SpawnedEnemies[Enemy];
	if(token.bIsAvailable)
	{
		token.bIsAvailable = false;
		Enemy->OnTokenGranted();
		Enemy->OnAttackTokenConsumed.AddUObject(this, &UAICoordinator::OnGrantedTokenConsumed);
	}
	else
	{
		token.bIsAvailable = true;
	}

	StartTokenGranting();
}

void UAICoordinator::SetTokenInCooldown(FAttackToken& InToken)
{
	const UGameplaySettings* GameplaySettings = GetDefault<UGameplaySettings>();

	UWorld* world = GetWorld();
	if (world)
	{
		FTimerDelegate timerFunction;
		timerFunction.BindUFunction(this, FName("ResetToken"), InToken);
		world->GetTimerManager().SetTimer(InToken.CooldownTimerHandle, timerFunction, GameplaySettings->GlobalTokenCooldown, false);
	}
}

void UAICoordinator::HandleCombatStart(FCombatSettings CombatSettings, const TArray<AACorridor*>& GameplayCorridors)
{
	for (AACorridor* Corridor : GameplayCorridors)
	{
		if (Corridor != nullptr)
		{
			FVector SpawnLocation = Corridor->GetEnemySpawnLocation();
			UWorld * World = GetWorld();

			if (IsValid(World))
			{
				int randomIndex = FMath::RandRange(0, CombatSettings.enemyEntries.Num() - 1);
				AABaseEnemy* NewEnemy = World->SpawnActor<AABaseEnemy>(CombatSettings.enemyEntries[randomIndex], SpawnLocation, FRotator::ZeroRotator);
				Corridor->SetIsOccupiedByEnemy(true);
				SpawnedEnemies.Add(NewEnemy, FAttackToken());
				NewEnemy->OnDeath.AddUObject(this, &UAICoordinator::OnEnemyDeath);
			}
		}
	}
	//Grant first token to a random enemy
	StartTokenGranting();
}

void UAICoordinator::ResetToken(FAttackToken& InToken)
{
	InToken.CooldownTimerHandle.Invalidate();
	InToken.bIsAvailable = true;
}

void UAICoordinator::StartTokenGranting()
{
	UWorld* world = GetWorld();
	if (world)
	{
		const UGameplaySettings* GameplaySettings = GetDefault<UGameplaySettings>();

		FTimerDelegate timerFunction;
		int randomIndex = FMath::RandRange(0, SpawnedEnemies.Num() - 1);
		
		TArray<AABaseEnemy*> Values;
		SpawnedEnemies.GenerateKeyArray(Values);

		timerFunction.BindUFunction(this, FName("GrantAttackToken"), Values[randomIndex]);
		world->GetTimerManager().SetTimer(GrantTokenTimerHandle, timerFunction, GameplaySettings->TokenGrantingRate, false);
	}
}


void UAICoordinator::HandlePostLoadMap(UWorld* World, const FWorldInitializationValues WorldInitializationValues)
{
	if (!World) return;

	UE_LOG(LogTemp, Log, TEXT("Level loaded: %s"), *World->GetName());
}

void UAICoordinator::OnGrantedTokenConsumed(AABaseEnemy* Enemy)
{
	Enemy->OnAttackTokenConsumed.RemoveAll(this);
	
	FAttackToken& GrantedToken = SpawnedEnemies[Enemy];

	SetTokenInCooldown(GrantedToken);
	Enemy->OnAttackTokenConsumed.RemoveAll(this);
}

void UAICoordinator::OnEnemyDeath(AABaseEnemy* Enemy)
{
	Enemy->OnDeath.RemoveAll(this);

	FAttackToken& GrantedToken = SpawnedEnemies[Enemy];

	SetTokenInCooldown(GrantedToken);
	Enemy->OnAttackTokenConsumed.RemoveAll(this);
		
	SpawnedEnemies.FindAndRemoveChecked(Enemy);
	Enemy->Destroy();	
}
