// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Components/BoxComponent.h>
#include "AirEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAirEnemyDeath);
class AAIController;

UCLASS()
class TETRISGANG_API AAirEnemy : public APawn
{
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  AAirEnemy();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  UPROPERTY()
  FAirEnemyDeath AirEnemyDeath;

  UPROPERTY()
  AAIController* AIController;

  UFUNCTION()
  void EnemyDeath();

  UFUNCTION()
  void Reactivate();

  UFUNCTION()
  void Deactivate();

  UPROPERTY(EditAnyWhere, BlueprintReadWrite)
  UBoxComponent* BoxCollision;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite)
  UStaticMeshComponent* AirMesh;
};
