// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "CPPGameProjectHud.generated.h"


UCLASS(config = Game)
class ACPPGameProjectHud : public AHUD
{
	GENERATED_BODY()

public:
	ACPPGameProjectHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
};
