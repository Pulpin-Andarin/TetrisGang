// Copyright Epic Games, Inc. All Rights Reserved.

#include "TetrisGangGameMode.h"
#include "TetrisGangCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATetrisGangGameMode::ATetrisGangGameMode()
  : Super()
{
  // set default pawn class to our Blueprinted character
  static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
  DefaultPawnClass = PlayerPawnClassFinder.Class;
  CurrentLevel = 1;

}

void ATetrisGangGameMode::UpdateEnemyCounter()
{
  CurrentEnemyDeaths++;

  if (CurrentEnemyDeaths >= DeathsPerLevel)
  {
    CurrentEnemyDeaths = 0;
    UpdateLevel();
  }
}

void ATetrisGangGameMode::UpdateLevel()
{
  if (CurrentLevel < MaxLevel)
  {
    CurrentLevel++;
  }

}


