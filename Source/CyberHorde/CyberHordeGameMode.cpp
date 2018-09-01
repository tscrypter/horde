// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CyberHordeGameMode.h"
#include "CyberHordeHUD.h"
#include "CyberHordeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACyberHordeGameMode::ACyberHordeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACyberHordeHUD::StaticClass();
}
