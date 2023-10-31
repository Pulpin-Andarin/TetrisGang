// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Utils/Constantes.h"
#include "TetrisGangProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;
class UStaticMesh;
class ATetrisGangGameMode;
class ATetrisPiece;
//class UTetrisPiece;


UCLASS(config = Game)
class ATetrisGangProjectile : public AActor
{
  GENERATED_BODY()

public:

  /** Sphere collision component */
  UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
  USphereComponent* CollisionComp;

  /** Projectile movement component */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
  UProjectileMovementComponent* ProjectileMovement;

  UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
  ATetrisGangGameMode* GameMode;

  UPROPERTY(EditAnywhere, BlueprintReadwrite)
  ATetrisPiece* TetrisPieceChild;

  UPROPERTY(EditAnywhere, BlueprintReadwrite)
  UChildActorComponent* ChildActor;

  UPROPERTY(VisibleAnywhere, BlueprintReadwrite)
  FVector ShootDirection;

  FTimerDelegate _timerDelegate;

  FTimerHandle ReturnTimerHandler;

  float LifeSpan = 3.0f;

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

  UFUNCTION()
  void Reactivate();

  UFUNCTION()
  void ActivateReturnToPoolTimer();

  UFUNCTION()
  void Deactivate();

  UFUNCTION()
  bool CheckPieceAndRotation(TetrisPieceColor p, TetrisPieceRotation R);
};

