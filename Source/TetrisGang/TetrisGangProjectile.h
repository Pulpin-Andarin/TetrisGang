// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Constantes.h"
#include "TetrisGangProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS(config=Game)
class ATetrisGangProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY()
	UStaticMeshComponent* PieceMesh;
public:
	ATetrisGangProjectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Rotation)
	Rotations rotation;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Type)
	Pieces piece;

	UFUNCTION(BlueprintCallable)
	void Rotate(Rotations newRotation);

	UFUNCTION()
	void UpdateMesh(UStaticMesh *NewMesh);
	
};

