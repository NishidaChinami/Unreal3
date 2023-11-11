// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootingGameMode.h"
#include "ShootingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootingGameMode::AShootingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
