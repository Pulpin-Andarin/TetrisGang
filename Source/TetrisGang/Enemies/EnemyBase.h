// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.generated.h"

class ATetrisPiece;
UINTERFACE(MinimalAPI, Blueprintable)
class UEnemyBaseInterface : public UInterface
{
  GENERATED_BODY()
};

class IEnemyBaseInterface
{
  GENERATED_BODY()

public:

  //UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  ATetrisPiece* TetrisChestPiece;

};

