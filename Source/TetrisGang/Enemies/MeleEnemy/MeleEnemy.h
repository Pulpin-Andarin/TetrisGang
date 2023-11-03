// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <TetrisGang/Utils/Constantes.h>
#include "../EnemyBase.h"
#include "MeleEnemy.generated.h"

class UWalkToComponent;
class UCapsuleComponent;
class UCharacterMovementComponent;
class AAIController;
class UTexture2D;
class UBillboardComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMeleEnemyDeath);

UCLASS()
class TETRISGANG_API AMeleEnemy : public ACharacter, public IEnemyBaseInterface
{
  GENERATED_BODY()

public:
  // Sets default values for this character's properties
  AMeleEnemy();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  bool bIsActive;

  UPROPERTY(EditAnywhere)
  UCapsuleComponent* CapsuleComponentCollision;

  UPROPERTY(VisibleAnywhere)
  UCharacterMovementComponent* MovementComponent;

  UPROPERTY(BlueprintReadWrite)
  AAIController* AICharacterController;

  float InitialSpeed = 0.0f;

  UPROPERTY()
  FMeleEnemyDeath MeleEnemyDeath;

  UFUNCTION()
  void EnemyDeath();

  UFUNCTION()
  virtual void Reactivate() override;

  UFUNCTION()
  virtual void Deactivate() override;

  UFUNCTION()
  virtual void ReturnToPool() override;

};
