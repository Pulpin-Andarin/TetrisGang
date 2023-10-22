// Copyright Epic Games, Inc. All Rights Reserved.

#include "TetrisGangGameMode.h"
#include "TetrisGangCharacter.h"
#include "./PooledPork/PooledPork.h"
#include "UObject/ConstructorHelpers.h"
#include <Kismet/GameplayStatics.h>
#include "./Spawns/Spawn.h"

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

void ATetrisGangGameMode::Initialize()
{
  Pool = Cast<APooledPork>(UGameplayStatics::GetActorOfClass(GetWorld(), APooledPork::StaticClass()));
  if (IsValid(Pool))
  {
    TArray<AActor*> Spawns;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawn::StaticClass(), Spawns);
    for (AActor* A : Spawns)
    {
      ASpawn* Spawn = Cast<ASpawn>(A);
      Pool->PoolCreated.AddDynamic(Spawn, &ASpawn::Initialize);
    }

    Pool->InitializePool();
  }
}




