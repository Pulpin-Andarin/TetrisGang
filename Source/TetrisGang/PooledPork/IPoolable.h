// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPoolable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIPoolable : public UInterface
{
  GENERATED_BODY()
};

/**
 *
 */
class TETRISGANG_API IIPoolable
{
  GENERATED_BODY()

  // Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

  virtual void Reactivate() = 0;

  virtual void Deactivate() = 0;

  virtual void ReturnToPool() = 0;

  bool bisActive = false;
};
