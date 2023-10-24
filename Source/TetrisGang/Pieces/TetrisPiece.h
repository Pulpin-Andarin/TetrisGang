// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Utils/Constantes.h"
#include "TetrisPiece.generated.h"

UCLASS()
class TETRISGANG_API ATetrisPiece : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ATetrisPiece();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Color of the piece
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  Pieces PieceColor;

  //Actual Rotation of the piece
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  Rotations PieceRotation;

  // Actual Mesh of the piece
  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UStaticMeshComponent* PieceMesh;
};
