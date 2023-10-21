// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class TETRISGANG_API AEnemyProjectile : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AEnemyProjectile();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  //UFUNCTION(BlueprintAssignable)
  //void Reactivate();

  //UFUNCTION(BlueprintAssignable)
  //void Deactivate();

};
