// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TetrisGangGameMode.generated.h"

UCLASS(minimalapi)
class ATetrisGangGameMode : public AGameModeBase
{
  GENERATED_BODY()

public:
  ATetrisGangGameMode();

  UPROPERTY()
  int CurrentLevel;

  UPROPERTY(VisibleAnywhere)
  int CurrentEnemyDeaths=0; 
  
  UPROPERTY(EditAnywhere)
   int DeathsPerLevel=10;  
   
   UPROPERTY(EditAnywhere)
   int MaxLevel =10;

  UFUNCTION()
  void UpdateEnemyCounter();

  UFUNCTION()
  void UpdateLevel();

};



