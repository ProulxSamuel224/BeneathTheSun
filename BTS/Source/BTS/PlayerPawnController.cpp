// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnController.h"
#include "UGameManager.h"

void APlayerPawnController::BeginPlay()
{
	Super::BeginPlay();
    
    check(InputComponent);
    InputComponent->BindAction("MoveUp", EInputEvent::IE_Pressed, this, &APlayerPawnController::MoveUp);
    InputComponent->BindAction("MoveDown", EInputEvent::IE_Pressed, this, &APlayerPawnController::MoveDown);
}

void APlayerPawnController::MoveUp()
{
    UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();

    EMovementType MovementType = EMovementType::MoveUp;
    if (IsValid(GameManager))
    {
        GameManager->MovePlayerPawnOnCorridor(MovementType);
    }
    
    GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "MoveUp", false);
}

void APlayerPawnController::MoveDown()
{
    UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();

    EMovementType MovementType = EMovementType::MoveDown;
    
    if (IsValid(GameManager))
    {
        GameManager->MovePlayerPawnOnCorridor(MovementType);
    }

    GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "MoveDown", false);
}
