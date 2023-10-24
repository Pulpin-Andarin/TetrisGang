// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../Utils/Constantes.h"
#include "TP_WeaponComponent.generated.h"

class ATetrisGangCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShoot);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TETRISGANG_API UTP_WeaponComponent : public USkeletalMeshComponent
{
  GENERATED_BODY()

public:
  /** Projectile class to spawn */
  UPROPERTY(EditDefaultsOnly, Category = Projectile)
  TSubclassOf<class ATetrisGangProjectile> ProjectileClass;

  /** Sound to play each time we fire */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
  USoundBase* FireSound;

  /** AnimMontage to play each time we fire */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
  UAnimMontage* FireAnimation;

  /** Gun muzzle's offset from the characters location */
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
  FVector MuzzleOffset;

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
  TArray<UStaticMesh*> AvailablePiecesMeshes;

  /** MappingContext */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputMappingContext* FireMappingContext;

  /** Fire Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputAction* FireAction;

  /** Rotate Bullet Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* RotateBulletLeftAction;


  /** Rotate Bullet Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* RotateBulletRightAction;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  UStaticMeshComponent* StaticProjectile;

  UPROPERTY(BlueprintAssignable)
	  FShoot ShootEvent;

  /** Sets default values for this component's properties */
  UTP_WeaponComponent();

  /** Attaches the actor to a FirstPersonCharacter */
  UFUNCTION(BlueprintCallable, Category = "Weapon")
  void AttachWeapon(ATetrisGangCharacter* TargetCharacter);

  /** Make the weapon Fire a Projectile */
  UFUNCTION(BlueprintCallable, Category = "Weapon")
  void Fire();

  UFUNCTION()
  void CreateRandomProjectile();

  UFUNCTION()
  void RotateBulletLeft();

  UFUNCTION()
  void RotateBulletRight();

  UFUNCTION()
  void UpdateProjectile();


  UPROPERTY(EditAnywhere, BlueprintReadWrite)
	  Pieces NextPiece = Pieces::Red;


protected:
  /** Ends gameplay for this component. */
  UFUNCTION()
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
  /** The Character holding this weapon*/
  ATetrisGangCharacter* Character;

  UPROPERTY(VisibleAnyWhere)
  Rotations ActualRotation = Rotations::Up;

  UPROPERTY(VisibleAnyWhere)
  Pieces ActualPiece = Pieces::Blue;


  UPROPERTY(VisibleAnyWhere)
  Rotations NextRotation = Rotations::Up;

  UPROPERTY(VisibleAnyWhere)
  UStaticMesh* ActualMesh;


};