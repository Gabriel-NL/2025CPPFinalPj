// Copyright Epic Games, Inc. All Rights Reserved.

#include "CPPGameProjectGameMode.h"
#include "CPPGameProjectPawn.h"
#include "CPPGameProjectHud.h"

ACPPGameProjectGameMode::ACPPGameProjectGameMode()
{
	DefaultPawnClass = ACPPGameProjectPawn::StaticClass();
	HUDClass = ACPPGameProjectHud::StaticClass();
}
