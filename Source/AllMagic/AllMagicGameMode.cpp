// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AllMagicGameMode.h"
#include "AllMagicCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAllMagicGameMode::AAllMagicGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
