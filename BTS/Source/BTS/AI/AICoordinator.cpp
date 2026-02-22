// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS/AI/AICoordinator.h"
#include "BTS/GameFramework/GameplaySettings.h"

void UAICoordinator::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UGameplaySettings* GameplaySettings = GetDefault<UGameplaySettings>();
	const FAttackToken InitToken;
	AvailableAttackTokens.Init(InitToken, GameplaySettings->MaxAIAttackTokens);

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
				AABaseEnemy* NewEnemy = World->SpawnActor<AABaseEnemy>(CombatSettings.enemyEntries[0], SpawnLocation, FRotator::ZeroRotator);
				Corridor->SetIsOccupiedByEnemy(true);
				SpawnedEnemies.Add(NewEnemy);
			}
		}
	}
}

void UAICoordinator::ResetToken(FAttackToken& InToken)
{
	InToken.CooldownTimerHandle.Invalidate();
}


void UAICoordinator::HandlePostLoadMap(UWorld* World, const FWorldInitializationValues WorldInitializationValues)
{
	if (!World) return;

	UE_LOG(LogTemp, Log, TEXT("Level loaded: %s"), *World->GetName());


}