// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "soundGameMode.h"
#include "soundCharacter.h"
#include "UObject/ConstructorHelpers.h"

AsoundGameMode::AsoundGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
