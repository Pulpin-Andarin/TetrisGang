// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <TetrisGang/Utils/Constantes.h>
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
class TETRISGANG_API AMeleEnemy : public ACharacter
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

  UFUNCTION()
  void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult);


  bool bIsActive;

  UPROPERTY(EditAnywhere)
  UCapsuleComponent* CapsuleComponentCollision;

  UPROPERTY(VisibleAnywhere)
  UCharacterMovementComponent* MovementComponent;

  UPROPERTY(BlueprintReadWrite)
  AAIController* AICharacterController;

  float InitialSpeed = 0.0f;

  UPROPERTY(VisibleAnywhere)
  Rotations PieceRotation;

  UPROPERTY(VisibleAnywhere)
  Pieces Pieces;


  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UStaticMeshComponent* StaticProjectile;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UStaticMeshComponent* StaticProjectileElDeverda;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<UTexture2D*> YellowTextures;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<UTexture2D*> CyamTextures;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<UTexture2D*> GreenTextures;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<UTexture2D*> RedTextures;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<UTexture2D*> OrangeTextures;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<UTexture2D*> BlueTextures;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TArray<UTexture2D*> PurpleTextures;

  UPROPERTY()
  UBillboardComponent* BillboardComponent;

  UPROPERTY()
  FMeleEnemyDeath MeleEnemyDeath;

  UFUNCTION()
  void EnemyDeath();

  UFUNCTION()
  void Reactivate();

  UFUNCTION()
  void Deactivate();

  UFUNCTION()
  void SelectPieceMesh();

};
