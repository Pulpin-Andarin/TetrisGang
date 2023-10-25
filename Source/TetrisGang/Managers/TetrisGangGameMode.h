// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TetrisGangGameMode.generated.h"

class APooledPork;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelUp);

UCLASS(minimalapi)
class ATetrisGangGameMode : public AGameModeBase
{
  GENERATED_BODY()

public:
  ATetrisGangGameMode();



  UPROPERTY()
  int CurrentLevel = 0;

  UPROPERTY(VisibleAnywhere)
  int CurrentEnemyDeaths = 0;

  UPROPERTY(EditAnywhere)
  int DeathsPerLevel = 10;

  UPROPERTY(EditAnywhere)
  int TotalPoints = 0;

  UPROPERTY(EditAnywhere)
  int MaxLevel = 10;

  UFUNCTION()
  void UpdateEnemyCounter();

  UFUNCTION()
  void UpdateLevel();

  APooledPork* Pool;

  virtual void BeginPlay() override;

  void Initialize();


  UPROPERTY(BlueprintAssignable)
  FLevelUp LevelUpEvent;
};



