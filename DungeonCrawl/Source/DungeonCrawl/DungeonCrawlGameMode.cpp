// Copyright Epic Games, Inc. All Rights Reserved.

#include "DungeonCrawlGameMode.h"
#include "DungeonCrawlCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADungeonCrawlGameMode::ADungeonCrawlGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
