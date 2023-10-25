// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../Utils/Constantes.h"
#include "TP_WeaponComponent.generated.h"

class ATetrisGangCharacter;
class ATetrisPiece;
class ATetrisGangGameMode;

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

  //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
  //TArray<UStaticMesh*> AvailablePiecesMeshes;


  virtual void BeginPlay() override;

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

  UPROPERTY(BlueprintAssignable)
  FShoot ShootEvent;

  //UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  //UStaticMeshComponent* CapuslePositionComponent;

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
  void UpdateProjectileIndicator();

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  TetrisPieceColor NextPieceColor = TetrisPieceColor::Red;

  UPROPERTY(VisibleAnyWhere)
  TetrisPieceRotation NextPieceRotation = TetrisPieceRotation::Up;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  ATetrisPiece* TetrisPiece;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  /** The Character holding this weapon*/
  ATetrisGangCharacter* Character;

protected:
  /** Ends gameplay for this component. */
  UFUNCTION()
  virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

  ATetrisGangGameMode* GameMode;

  UStaticMeshComponent* MuzzlePosition;

};