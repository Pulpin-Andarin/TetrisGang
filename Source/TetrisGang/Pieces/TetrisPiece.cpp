// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisPiece.h"

// Sets default values
ATetrisPiece::ATetrisPiece()
{
  PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Piece Mesh Component"));

  // Use a sphere as a simple collision representation
  PieceMesh->BodyInstance.SetCollisionProfileName("Projectile");
  //PieceMesh->OnComponentHit.AddDynamic(this, &ATetrisGangProjectile::OnHit);		// set up a notification for when this component hits something blocking

  // Players can't walk on it
  PieceMesh->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
  PieceMesh->CanCharacterStepUpOn = ECB_No;

  static ConstructorHelpers::FObjectFinder<UDataTable> TetrisPiecesDataObject(TEXT("/Script/Engine.DataTable'/Game/Assets/DT_TetrisPieces.DT_TetrisPieces'"));
  if (TetrisPiecesDataObject.Succeeded())
  {
    TetrisPiecesDataTable = TetrisPiecesDataObject.Object;
  }

  static ConstructorHelpers::FObjectFinder<UDataTable> TetrisRotationsDataObject(TEXT("/Script/Engine.DataTable'/Game/Assets/DT_TetrisRotations.DT_TetrisRotations'"));

  if (TetrisRotationsDataObject.Succeeded())
  {
    TetrisRotationsDataTable = TetrisRotationsDataObject.Object;
  }
}

void ATetrisPiece::RotateClockwise()
{
  switch (PieceRotation) {
  case TetrisPieceRotation::Up:
    PieceRotation = TetrisPieceRotation::Right;
    break;
  case TetrisPieceRotation::Right:
    PieceRotation = TetrisPieceRotation::Down;
    break;
  case TetrisPieceRotation::Down:
    PieceRotation = TetrisPieceRotation::Left;
    break;
  case TetrisPieceRotation::Left:
    PieceRotation = TetrisPieceRotation::Up;
    break;
  default:
    UE_LOG(LogTemp, Error, TEXT("Rotation error!!!!!"));
    break;
  }
  ChangeMeshRotation(PieceRotation, *TetrisRotationsDataTable, *PieceMesh);
}

void ATetrisPiece::RotateCounterClockwise()
{
  switch (PieceRotation) {
  case TetrisPieceRotation::Up:
    PieceRotation = TetrisPieceRotation::Left;
    break;
  case TetrisPieceRotation::Left:
    PieceRotation = TetrisPieceRotation::Down;
    break;
  case TetrisPieceRotation::Down:
    PieceRotation = TetrisPieceRotation::Right;
    break;
  case TetrisPieceRotation::Right:
    PieceRotation = TetrisPieceRotation::Up;
    break;
  default:
    UE_LOG(LogTemp, Error, TEXT("Rotation error!!!!!"));
    break;
  }
  ChangeMeshRotation(PieceRotation, *TetrisRotationsDataTable, *PieceMesh);
}




