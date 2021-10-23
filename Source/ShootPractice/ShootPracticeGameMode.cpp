// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootPracticeGameMode.h"
#include "ShootPracticeHUD.h"
#include "ShootPracticeCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPlayerState.h"
AShootPracticeGameMode::AShootPracticeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShootPracticeHUD::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
}
