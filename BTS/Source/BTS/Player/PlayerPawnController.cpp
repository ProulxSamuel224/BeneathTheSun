// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnController.h"

void APlayerPawnController::BeginPlay()
{
	Super::BeginPlay();
 

    PlayerPawn = Cast<APlayerPawn>(GetOwner());
}
//
//void APlayerPawnController::MoveUp()
//{
//    UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();
//
//    EMovementType MovementType = EMovementType::MoveUp;
//    if (IsValid(GameManager))
//    {
//        GameManager->MovePlayerPawnOnCorridor(MovementType);
//    }
//    
//    GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "MoveUp", false);
//}
//
//void APlayerPawnController::MoveDown()
//{
//    UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();
//
//    EMovementType MovementType = EMovementType::MoveDown;
//    
//    if (IsValid(GameManager))
//    {
//        GameManager->MovePlayerPawnOnCorridor(MovementType);
//    }
//
//    GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "MoveDown", false);
//}
//
//void APlayerPawnController::TargetUp()
//{
//    UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();
//
//    GameManager->UpdateTargettedCorridor(true);
//    GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "SelectTargetUp", false);
//}
//
//void APlayerPawnController::TargetDown()
//{
//   UUGameManager* GameManager = GetGameInstance()->GetSubsystem<UUGameManager>();
//   
//   GameManager->UpdateTargettedCorridor(false);
//   GEngine->AddOnScreenDebugMessage(3, 10, FColor::Red, "SelectTargetDown", false);
//}
