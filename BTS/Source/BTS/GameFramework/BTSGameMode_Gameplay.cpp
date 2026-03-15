// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS/GameFramework/BTSGameMode_Gameplay.h"
#include "GameplaySettings.h"
#include "Kismet/GameplayStatics.h"
#include <BTS/AI/AICoordinator.h>
#include "UGameManager.h"

void ABTSGameMode_Gameplay::BeginPlay()
{
	Super::BeginPlay();
	const UGameplaySettings* GameplaySettings = GetDefault<UGameplaySettings>();
	UAICoordinator* AICoordinator = GetGameInstance()->GetSubsystem<UAICoordinator>();
	UUGameManager* GameManager= GetGameInstance()->GetSubsystem<UUGameManager>();

	GameManager->SpawnCorridor(FVector::ZeroVector);
	AActor* playerActor = UGameplayStatics::GetActorOfClass(GetWorld(), DefaultPawnClass);
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(playerActor);
	GameManager->SpawnPlayer(PlayerPawn);
	
	AICoordinator->HandleCombatStart(GameplaySettings->DefaultCombatSettings, GameManager->GetGameplayCorridors());

}
