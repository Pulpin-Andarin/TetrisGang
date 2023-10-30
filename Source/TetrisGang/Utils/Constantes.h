// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "Constantes.generated.h"

UENUM(BlueprintType)
enum class TetrisPieceRotation : uint8
{
  Up UMETA(DisplayName = "Up"),
  Right UMETA(DisplayName = "Right"),
  Down UMETA(DisplayName = "Down"),
  Left UMETA(DisplayName = "Left")
};

UENUM(BlueprintType)
enum class TetrisPieceColor : uint8
{
  Yelow UMETA(DisplayName = "Yelow"),
  Cyan UMETA(DisplayName = "Cyan"),
  Green UMETA(DisplayName = "Green"),
  Red UMETA(DisplayName = "Red"),
  Orange UMETA(DisplayName = "Orange"),
  Blue UMETA(DisplayName = "Blue"),
  Purple UMETA(DisplayName = "Purple")
};


USTRUCT(BlueprintType)
struct FTetrisRotationData : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  FVector RotationOfThePiece;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  TetrisPieceRotation Rotation;
};

USTRUCT(BlueprintType)
struct FTetrisPiecesData : public FTableRowBase
{
  GENERATED_BODY()

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  UStaticMesh* PieceMesh;

  UPROPERTY(EditAnywhere, BlueprintReadOnly)
  TetrisPieceColor Piece;
};


/**
 *
 */
class TETRISGANG_API Constantes
{

private:
  // Get name of the row in datatable
  inline static FName GetDisplayName(TetrisPieceRotation NameOfThePiece)
  {
    switch (NameOfThePiece)
    {
    case TetrisPieceRotation::Up:
      return FName(TEXT("Up"));

    case TetrisPieceRotation::Left:
      return FName(TEXT("Left"));

    case TetrisPieceRotation::Down:
      return FName(TEXT("Down"));

    case TetrisPieceRotation::Right:
      return FName(TEXT("Right"));
    default:
      return FName(TEXT("Error"));
    }
  };

  // Get name of the row in datatable
  inline static FName GetDisplayName(TetrisPieceColor NameOfThePiece)
  {
    switch (NameOfThePiece)
    {
    case TetrisPieceColor::Blue:
      return FName(TEXT("Blue"));

    case TetrisPieceColor::Cyan:
      return FName(TEXT("Cyan"));

    case TetrisPieceColor::Green:
      return FName(TEXT("Green"));

    case TetrisPieceColor::Orange:
      return FName(TEXT("Orange"));

    case TetrisPieceColor::Purple:
      return FName(TEXT("Purple"));

    case TetrisPieceColor::Red:
      return FName(TEXT("Red"));

    case TetrisPieceColor::Yelow:
      return FName(TEXT("Yellow"));
    default:
      return FName(TEXT("Error"));
    }
  };

public:

  inline static TetrisPieceRotation GetRandomRotation() {
    return TetrisPieceRotation(rand() % 4);
  };

  inline static TetrisPieceColor GetRandomPiece()
  {
    return TetrisPieceColor(rand() % 7);
  };

  inline static FVector GetRotation(UDataTable* RotationsDataTable, TetrisPieceRotation PieceRotation)
  {
    static const FString ContextString(TEXT("Tetris Rotation Data Context"));

    FName RowName = GetDisplayName(PieceRotation);

    FTetrisRotationData* RDT = RotationsDataTable->FindRow<FTetrisRotationData>(RowName, ContextString);

    if (RDT)
    {
      return RDT->RotationOfThePiece;
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Rotation Not found!!!!!"));
      return FVector::Zero();
    }
  };

  inline static UStaticMesh* GetMesh(UDataTable* TetrisPiecesDataTable, TetrisPieceColor PieceColor)
  {
    static const FString ContextString(TEXT("Tetris Rotation Data Context"));

    FName RowName = GetDisplayName(PieceColor);

    FTetrisPiecesData* TPDT = TetrisPiecesDataTable->FindRow<FTetrisPiecesData>(RowName, ContextString);
    if (TPDT)
    {
      return TPDT->PieceMesh;
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Mesh Not found!!!!!"));
      return nullptr;
    }
  };

};
