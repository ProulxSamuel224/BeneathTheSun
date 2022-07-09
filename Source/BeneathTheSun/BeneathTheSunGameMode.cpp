// Copyright Epic Games, Inc. All Rights Reserved.

#include "BeneathTheSunGameMode.h"
#include "BeneathTheSunPawn.h"

ABeneathTheSunGameMode::ABeneathTheSunGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ABeneathTheSunPawn::StaticClass();
}

