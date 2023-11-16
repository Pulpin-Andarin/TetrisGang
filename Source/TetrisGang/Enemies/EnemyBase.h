// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TetrisGang/PooledPork/IPoolable.h"
#include "TetrisGang/Utils/Constantes.h"
#include "TetrisGang/Pieces/TetrisPiece.h"
#include "TetrisGang/Managers/TetrisGangGameMode.h"
#include "EnemyBase.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UEnemyBaseInterface : public UInterface
{
  GENERATED_BODY()
};

class IEnemyBaseInterface : public IIPoolable
{
  GENERATED_BODY()

public:

  //UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  ATetrisPiece* TetrisChestPiece;

  ATetrisGangGameMode* GameMode;

  //UFUNCTION()
  virtual inline void SetRandomPieceInChest() {
    TetrisChestPiece->PieceColor = Constantes::GetRandomPiece();
    TetrisChestPiece->PieceRotation = Constantes::GetRandomRotation();
    TetrisChestPiece->PieceMesh->SetStaticMesh(Constantes::GetMesh(TetrisChestPiece->TetrisPiecesDataTable, TetrisChestPiece->PieceColor));
    FVector rot = Constantes::GetRotation(TetrisChestPiece->TetrisRotationsDataTable, TetrisChestPiece->PieceRotation);
    TetrisChestPiece->PieceMesh->SetRelativeRotation(FRotator(rot.X, rot.Y, rot.Z));
  };


  // Inherited via IIPoolable
  virtual inline void Reactivate() override {
    SetRandomPieceInChest();
    bisActive = true;
  };

  virtual inline void Deactivate() override
  {
    bisActive = false;
  };

  virtual inline void EnemyDeath() = 0;

  // Inherited via IIPoolable
  inline void ReturnToPool() override
  {

    Deactivate();
    EnemyDeath();
  };


  //void IEnemyBaseInterface::ReturnToPool()
  //{
  //  //AAirEnemy* AirEnemy = Cast<AAirEnemy>(&ActorToPool);
  //  AirEnemy->Deactivate();
  //  AirEnemy->SetActorLocation(PoolLocation);
  //  //AirEnemies.Push(AirEnemy);
  //}


};

