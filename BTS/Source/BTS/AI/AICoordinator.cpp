// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS/AI/AICoordinator.h"
#include "BTS/GameFramework/GameplaySettings.h"

void UAICoordinator::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UGameplaySettings* GameplaySettings = GetDefault<UGameplaySettings>();
	
	AvailableAttackTokens.Init(FAttackToken(), GameplaySettings->MaxAIAttackTokens);

	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UAICoordinator::HandlePostLoadMap);
}

void UAICoordinator::Deinitialize()
{
	Super::Deinitialize();
}

void UAICoordinator::GrantAttackToken(AABaseEnemy* Enemy)
{
	FAttackToken Token = AvailableAttackTokens.Pop();
	Token.bIsAvailable = false;
	Token.bIsGranted = true;
	GrantedAttackTokens.Add(Token);
	Enemy->SetAttackToken(Token);
	Enemy->OnAttackTokenConsumed.AddUObject(this, &UAICoordinator::OnGrantedTokenConsumed);
}

void UAICoordinator::SetTokenInCooldown(FAttackToken& InToken)
{
	const UGameplaySettings* GameplaySettings = GetDefault<UGameplaySettings>();
	
	InToken.bIsGranted = false;

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
				AABaseEnemy* NewEnemy = World->SpawnActor<AABaseEnemy>(CombatSettings.enemyEntries[0], SpawnLocation, FRotator::ZeroRotator);
				Corridor->SetIsOccupiedByEnemy(true);
				SpawnedEnemies.Add(NewEnemy);
			}
		}
	}
	//Grant first token to a random enemy
	int randomIndex = FMath::RandRange(0, SpawnedEnemies.Num() - 1);
	GrantAttackToken(SpawnedEnemies[randomIndex]);

}

void UAICoordinator::ResetToken(FAttackToken& InToken)
{
	InToken.CooldownTimerHandle.Invalidate();
	InToken.bIsAvailable = true;
}


void UAICoordinator::HandlePostLoadMap(UWorld* World, const FWorldInitializationValues WorldInitializationValues)
{
	if (!World) return;

	UE_LOG(LogTemp, Log, TEXT("Level loaded: %s"), *World->GetName());


}

void UAICoordinator::OnGrantedTokenConsumed(AABaseEnemy* Enemy)
{
	Enemy->OnAttackTokenConsumed.RemoveAll(this);
	
	FAttackToken GrantedToken = Enemy->GetAttackToken();

	SetTokenInCooldown(GrantedToken);
	Enemy->OnAttackTokenConsumed.RemoveAll(this);

	GrantedAttackTokens.Remove(GrantedToken);
	AvailableAttackTokens.Add(GrantedToken);

	int randomIndex = FMath::RandRange(0, SpawnedEnemies.Num() - 1);
	GrantAttackToken(SpawnedEnemies[randomIndex]);
}
