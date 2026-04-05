// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS/GameFramework/BTSGameMode_Gameplay.h"
#include "GameplaySettings.h"
#include "Kismet/GameplayStatics.h"
#include "BTS/AI/AICoordinator.h"
#include "Blueprint/UserWidget.h"
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
	
	PlayerPawn->OnDeath.AddUObject(this, &ABTSGameMode_Gameplay::OnPlayerDeath);
	GameManager->SpawnPlayer(PlayerPawn);
	
	AICoordinator->HandleCombatStart(GameplaySettings->DefaultCombatSettings, GameManager->GetGameplayCorridors());
	AICoordinator->OnAllEnemiesKilled.AddUObject(this, &ABTSGameMode_Gameplay::OnAllEnemiesKilled);
}

void ABTSGameMode_Gameplay::OnPlayerDeath(APlayerPawn* PlayerPawn)  
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	if (GameOverWidgetClass)
	{
		GameOverWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		if (GameOverWidgetInstance)
		{
			GameOverWidgetInstance->AddToViewport();
		}
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		FInputModeUIOnly InputMode;

		// Optional: specify which widget to focus
		if (GameOverWidgetInstance)
		{
			InputMode.SetWidgetToFocus(GameOverWidgetInstance->TakeWidget());
		}

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void ABTSGameMode_Gameplay::OnAllEnemiesKilled()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	if (VictoryWidgetClass)
	{
		VictoryWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), VictoryWidgetClass);
		if (VictoryWidgetInstance)
		{
			VictoryWidgetInstance->AddToViewport();
		}
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		FInputModeUIOnly InputMode;

		// Optional: specify which widget to focus
		if (VictoryWidgetInstance)
		{
			InputMode.SetWidgetToFocus(VictoryWidgetInstance->TakeWidget());
		}

		PC->SetInputMode(InputMode);
		PC->bShowMouseCursor = true;
	}
}

void ABTSGameMode_Gameplay::LoadLevel(FName LevelToLoad)
{
	UGameplayStatics::OpenLevel(GetWorld(), LevelToLoad);
}
