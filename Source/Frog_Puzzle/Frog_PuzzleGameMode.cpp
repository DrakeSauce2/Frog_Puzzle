// Copyright Epic Games, Inc. All Rights Reserved.

#include "Frog_PuzzleGameMode.h"
#include "Frog_PuzzleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFrog_PuzzleGameMode::AFrog_PuzzleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
