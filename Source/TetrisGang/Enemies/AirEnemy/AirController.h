// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AirController.generated.h"

/**
 *
 */
UCLASS()
class TETRISGANG_API AAirController : public AAIController
{
  GENERATED_BODY()

  //bool ShouldPostponePathUpdates() const override;

  void OnPossess(APawn* InPawn) override;
};
