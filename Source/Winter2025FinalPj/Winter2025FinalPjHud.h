// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "Winter2025FinalPjHud.generated.h"


UCLASS(config = Game)
class AWinter2025FinalPjHud : public AHUD
{
	GENERATED_BODY()

public:
	AWinter2025FinalPjHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
