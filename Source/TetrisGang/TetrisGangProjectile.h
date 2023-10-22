// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Constantes.h"
#include "TetrisGangProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class UStaticMesh;
class ATetrisGangGameMode;

UCLASS(config = Game)
class ATetrisGangProjectile : public AActor
{
  GENERATED_BODY()

  /** Sphere collision component */
  UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
  USphereComponent* CollisionComp;

  /** Projectile movement component */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
  UProjectileMovementComponent* ProjectileMovement;


  UStaticMeshComponent* PieceMesh;

  ATetrisGangGameMode* GameMode;

protected:
  virtual void BeginPlay();

public:
  ATetrisGangProjectile();

  /** called when projectile hits something */
  UFUNCTION()
  void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

  /** Returns CollisionComp subobject **/
  USphereComponent* GetCollisionComp() const { return CollisionComp; }
  /** Returns ProjectileMovement subobject **/
  UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Rotation)
  Rotations Rotation;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Type)
  Pieces Piece;

  UFUNCTION(BlueprintCallable)
  void Rotate();

  UFUNCTION()
  void UpdateMesh(UStaticMesh* NewMesh);

  UFUNCTION()
  void Reactivate();

  UFUNCTION()
  void Deactivate();

  UFUNCTION()
  bool CheckPieceAndRotation(Pieces p, Rotations R);
};

