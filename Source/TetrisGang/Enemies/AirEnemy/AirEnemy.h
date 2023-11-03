// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Components/BoxComponent.h>
#include <TetrisGang/Utils/Constantes.h>
#include "../EnemyBase.h"
#include "AirEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAirEnemyDeath);
class AAIController;
class UTexture2D;
class UBillboardComponent;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class TETRISGANG_API AAirEnemy : public APawn, public IEnemyBaseInterface
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
  virtual void Reactivate() override;

  UFUNCTION()
  virtual void Deactivate() override;

  UFUNCTION()
  virtual void ReturnToPool() override;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite)
  UBoxComponent* BoxCollision;

  UPROPERTY(EditAnyWhere, BlueprintReadWrite)
  UStaticMeshComponent* AirMesh;

  //UPROPERTY(VisibleAnywhere)
  //TetrisPieceRotation PieceRotation;

  //UPROPERTY(VisibleAnywhere)
  //TetrisPieceColor Pieces;

  //void SelectPieceMesh();

  //UPROPERTY(EditAnywhere, BlueprintReadWrite)
  //TArray<UTexture2D*> YellowTextures;

  //UPROPERTY(EditAnywhere, BlueprintReadWrite)
  //TArray<UTexture2D*> CyamTextures;

  //UPROPERTY(EditAnywhere, BlueprintReadWrite)
  //TArray<UTexture2D*> GreenTextures;

  //UPROPERTY(EditAnywhere, BlueprintReadWrite)
  //TArray<UTexture2D*> RedTextures;

  //UPROPERTY(EditAnywhere, BlueprintReadWrite)
  //TArray<UTexture2D*> OrangeTextures;

  //UPROPERTY(EditAnywhere, BlueprintReadWrite)
  //TArray<UTexture2D*> BlueTextures;

  //UPROPERTY(EditAnywhere, BlueprintReadWrite)
  //TArray<UTexture2D*> PurpleTextures;

  //UPROPERTY()
  //UBillboardComponent* BillboardComponent;

};
