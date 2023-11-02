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

public:

  // Color of the piece
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  TetrisPieceColor PieceColor = TetrisPieceColor::Blue;

  //Actual Rotation of the piece
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  TetrisPieceRotation PieceRotation = TetrisPieceRotation::Up;

  // Actual rotation Value
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  FVector PieceRotationValue;

  // Actual Mesh of the piece
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  UStaticMeshComponent* PieceMesh;

  /** Add interface function declarations here */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  UDataTable* TetrisPiecesDataTable;

  /** Add interface function declarations here */
  UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
  UDataTable* TetrisRotationsDataTable;

public:

  void RotateCounterClockwise();

  void RotateClockwise();

  void InitDataAsset();

  ///---- Static inline functions --- 

  inline static void InitializeNewPiece(ATetrisPiece& TetrisPieceToUpdate, ATetrisPiece& NewTetrisPiece)
  {
    //Assign logic values
    TetrisPieceToUpdate.PieceRotation = NewTetrisPiece.PieceRotation;
    TetrisPieceToUpdate.PieceColor = NewTetrisPiece.PieceColor;

    //Update Mesh and rotation
    UStaticMesh* ProjectileMesh = Constantes::GetMesh(NewTetrisPiece.TetrisPiecesDataTable, NewTetrisPiece.PieceColor);

    if (ProjectileMesh)
    {
      TetrisPieceToUpdate.PieceMesh->SetStaticMesh(ProjectileMesh);

      ChangeMeshRotation(NewTetrisPiece.PieceRotation, *NewTetrisPiece.TetrisRotationsDataTable, *TetrisPieceToUpdate.PieceMesh);
    }
    else {
      UE_LOG(LogTemp, Error, TEXT("Projectile Mesh not found"));
    }
  }

  inline static void ChangeMeshRotation(TetrisPieceRotation R, UDataTable& RotationDataTable, UStaticMeshComponent& MeshToRotate)
  {
    FVector Rotation = Constantes::GetRotation(&RotationDataTable, R);
    if (Rotation != FVector::Zero())
    {
      MeshToRotate.SetRelativeRotation(FRotator(Rotation.X, Rotation.Y, Rotation.Z));
    }
    else {
      UE_LOG(LogTemp, Error, TEXT("Rotation not found"));
    }
  }

};
