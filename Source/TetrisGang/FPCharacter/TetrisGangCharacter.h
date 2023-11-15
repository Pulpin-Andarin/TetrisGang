// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TetrisGangCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDeath);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerHitted, int, ActualLife);

UCLASS(config = Game)
class ATetrisGangCharacter : public ACharacter
{
  GENERATED_BODY()

  /** Pawn mesh: 1st person view (arms; seen only by self) */
  UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
  USkeletalMeshComponent* Mesh1P;

  /** First person camera */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
  UCameraComponent* FirstPersonCameraComponent;

  /** MappingContext */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputMappingContext* DefaultMappingContext;

  /** Jump Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* JumpAction;

  /** Move Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  UInputAction* MoveAction;

public:
  ATetrisGangCharacter();

protected:
  virtual void BeginPlay();

public:

  /** Look Input Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputAction* LookAction;

  /** God Mode Action */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
  class UInputAction* GodModeAction;

  /** Bool for AnimBP to switch to another animation set */
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
  bool bHasRifle;

  /** Setter to set the bool */
  UFUNCTION(BlueprintCallable, Category = Weapon)
  void SetHasRifle(bool bNewHasRifle);

  /** Getter for the bool */
  UFUNCTION(BlueprintCallable, Category = Weapon)
  bool GetHasRifle();

  UFUNCTION(BlueprintCallable)
  void ReceiveDamage();

  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
  int Health = 7;

  UPROPERTY(BlueprintAssignable)
  FPlayerDeath PlayerDeath;

  UPROPERTY(BlueprintAssignable)
  FPlayerHitted PlayerHitted;

protected:
  /** Called for movement input */
  void Move(const FInputActionValue& Value);

  /** Called for looking input */
  void Look(const FInputActionValue& Value);

  /** Called for activate god mode input*/
  void ActivateGodMode(const FInputActionValue& Value);

protected:
  // APawn interface
  virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
  // End of APawn interface

public:
  /** Returns Mesh1P subobject **/
  USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
  /** Returns FirstPersonCameraComponent subobject **/
  UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

  UPROPERTY(EditAnywhere)
  bool bGodMode = false;

};


