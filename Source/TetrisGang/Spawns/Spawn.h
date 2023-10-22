// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawn.generated.h"

class ATetrisGangGameMode;
UCLASS()
class TETRISGANG_API ASpawn : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ASpawn();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:

  UFUNCTION(BlueprintCallable)
  void SpawnEnemy();

  FVector SpawnLocation;
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  UPROPERTY(EditAnywhere)
  float CooldownBetweenSpawns = 5.f;

  UPROPERTY(EditAnywhere)
  /* Handle to manage the timer */
  FTimerHandle FuzeTimerHandle;

  UFUNCTION()
  void Initialize();


  ATetrisGangGameMode* TetrisGameMode;

  UFUNCTION()
  void UpdateCooldown();

  TArray<float> Cooldowns;
};
