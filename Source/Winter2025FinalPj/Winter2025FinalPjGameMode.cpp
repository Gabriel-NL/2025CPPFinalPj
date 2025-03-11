// Copyright Epic Games, Inc. All Rights Reserved.

#include "Winter2025FinalPjGameMode.h"
#include "Winter2025FinalPjPawn.h"
#include "Winter2025FinalPjHud.h"

AWinter2025FinalPjGameMode::AWinter2025FinalPjGameMode()
{
	DefaultPawnClass = AWinter2025FinalPjPawn::StaticClass();
	HUDClass = AWinter2025FinalPjHud::StaticClass();
}
