// Copyright Epic Games, Inc. All Rights Reserved.

#include "ElectricZoneGameMode.h"
#include "ElectricZoneCharacter.h"
#include "UObject/ConstructorHelpers.h"

AElectricZoneGameMode::AElectricZoneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
