// Copyright Epic Games, Inc. All Rights Reserved.

#include "U08_FeaturesGameMode.h"
#include "U08_FeaturesPlayerController.h"
#include "U08_FeaturesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AU08_FeaturesGameMode::AU08_FeaturesGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AU08_FeaturesPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}