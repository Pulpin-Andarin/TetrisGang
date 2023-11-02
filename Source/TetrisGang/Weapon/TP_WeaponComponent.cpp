// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "../FPCharacter/TetrisGangCharacter.h"
#include "./Projectile/TetrisGangProjectile.h"
#include "TetrisGang/Pieces/TetrisPiece.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TetrisGang/Pieces/TetrisPiece.h"
#include "TetrisGang/Managers/TetrisGangGameMode.h"
#include "TetrisGang/PooledPork/PooledPork.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
  // Default offset from the character location for projectiles to spawn
  MuzzleOffset = FVector(20.0f, 0.0f, 10.0f);
  //CapuslePositionComponent = Cast<UStaticMeshComponent>(GetOwner()->FindComponentByTag<UStaticMeshComponent>(FName(TEXT("CapsulePosition"))));


  //TetrisPiece->SetupAttachment(GetOwner()->GetRootComponent());
  //TetrisPiece->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

}

void UTP_WeaponComponent::BeginPlay()
{
  Super::BeginPlay();
  GameMode = Cast<ATetrisGangGameMode>(GetWorld()->GetAuthGameMode());
  FName Tag = TEXT("Muzzle");
  MuzzlePosition = Cast<UStaticMeshComponent>(GetOwner()->FindComponentByTag<UStaticMeshComponent>(Tag));
}


void UTP_WeaponComponent::AttachWeapon(ATetrisGangCharacter* TargetCharacter)
{
  Character = TargetCharacter;

  // Check that the character is valid, and has no rifle yet
  if (Character == nullptr || Character->GetHasRifle())
  {
    return;
  }

  // Attach the weapon to the First Person Character
  FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
  AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

  // switch bHasRifle so the animation blueprint can switch to another animation set
  Character->SetHasRifle(true);

  // Set up action bindings
  if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
  {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
      // Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
      Subsystem->AddMappingContext(FireMappingContext, 1);
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
    {
      // Fire
      EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);

      // Rotate Bullet
      EnhancedInputComponent->BindAction(RotateBulletLeftAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::RotateBulletLeft);

      // Rotate Bullet
      EnhancedInputComponent->BindAction(RotateBulletRightAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::RotateBulletRight);
    }
  }

  UChildActorComponent& ChildActor = *Cast<UChildActorComponent>(GetOwner()->FindComponentByClass(UChildActorComponent::StaticClass()));
  TetrisPiece = Cast<ATetrisPiece>(ChildActor.GetChildActor());

  UStaticMeshComponent* CapuslePositionComponent = Cast<UStaticMeshComponent>(GetOwner()->FindComponentByTag<UStaticMeshComponent>(FName(TEXT("CapsulePosition"))));
  //ChildActor.AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
  //ChildActor.SetWorldLocation(CapuslePositionComponent->GetComponentLocation());
  //ChildActor.SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
  /*TetrisPiece->PieceMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));*/
  // 

  //Init indicator
  //TetrisPiece->SetWorldLocation(CapuslePositionComponent->GetComponentLocation());
  //TetrisPiece->AttachToComponent(CapuslePositionComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
  //TetrisPiece->SetWorldScale3D(FVector(4.f, 4.f, 4.f));
  UpdateProjectileIndicator();
}



void UTP_WeaponComponent::Fire()
{
  if (Character == nullptr || Character->GetController() == nullptr)
  {
    return;
  }

  if (ProjectileClass != nullptr)
  {
    UWorld* const World = GetWorld();
    if (World != nullptr)
    {
      APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
      const FRotator& SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
      const FVector& ForwardRotation = PlayerController->PlayerCameraManager->GetCameraRotation().Vector();

      //Set Spawn Collision Handling Override
      FActorSpawnParameters ActorSpawnParams;
      ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

      // Spawn the projectile at the muzzle
      AActor* ActorProjectile = GameMode->Pool->GetNextActor(ProjectileClass);
      if (ActorProjectile)
      {
        ATetrisGangProjectile* ActualProjectile = Cast<ATetrisGangProjectile>(ActorProjectile);/*World->SpawnActor<ATetrisGangProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);*/
        if (IsValid(ActualProjectile) && IsValid(TetrisPiece))
        {
          ActualProjectile->SetActorLocation(MuzzlePosition->GetComponentLocation());
          FVector LookAtCameraRotation = ActualProjectile->GetActorLocation() - PlayerController->PlayerCameraManager->GetCameraLocation();
          LookAtCameraRotation.Normalize();

          ActualProjectile->ProjectileMovement->Velocity = ForwardRotation * ActualProjectile->ProjectileMovement->InitialSpeed;
          ActualProjectile->ProjectileMovement->UpdateComponentVelocity();


          ATetrisPiece::InitializeNewPiece(*ActualProjectile->TetrisPieceChild, *TetrisPiece);

          ActualProjectile->TetrisPieceChild->SetActorRotation(TetrisPiece->GetActorRotation());
          //ActualProjectile->TetrisPieceChild->PieceMesh->SetRelativeRotation(FRotator(0, 0, 0));
        }
      }
    }

    // Try and play the sound if specified
    if (FireSound != nullptr)
    {
      UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
    }

    // Try and play a firing animation if specified
    if (FireAnimation != nullptr)
    {
      // Get the animation object for the arms mesh
      UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
      if (AnimInstance != nullptr)
      {
        AnimInstance->Montage_Play(FireAnimation, 1.f);
      }
    }

    CreateRandomProjectile();
    ShootEvent.Broadcast();
  }
}



void UTP_WeaponComponent::CreateRandomProjectile()
{
  TetrisPiece->PieceColor = NextPieceColor;
  TetrisPiece->PieceRotation = NextPieceRotation;
  NextPieceColor = Constantes::GetRandomPiece();
  NextPieceRotation = Constantes::GetRandomRotation();

  UpdateProjectileIndicator();
}


void UTP_WeaponComponent::UpdateProjectileIndicator()
{
  //Update Mesh and rotation
  UStaticMesh* ProjectileMesh = Constantes::GetMesh(TetrisPiece->TetrisPiecesDataTable, TetrisPiece->PieceColor);

  if (ProjectileMesh)
  {
    TetrisPiece->PieceMesh->SetStaticMesh(ProjectileMesh);

    ATetrisPiece::ChangeMeshRotation(TetrisPiece->PieceRotation, *TetrisPiece->TetrisRotationsDataTable, *TetrisPiece->PieceMesh);
    //FVector ProjectileRotation = Constantes::GetRotation(TetrisPiece->TetrisRotationsDataTable, TetrisPiece->PieceRotation);
    //if (ProjectileRotation != FVector::Zero())
    //{
    //  TetrisPiece->PieceMesh->SetRelativeRotation(FRotator(ProjectileRotation.X, ProjectileRotation.Y, ProjectileRotation.Z));
    //}
    //else {
    //  UE_LOG(LogTemp, Error, TEXT("Projectile Rotation not found"));
    //}
  }
  else {
    UE_LOG(LogTemp, Error, TEXT("Projectile Mesh not found"));
  }
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
  if (Character == nullptr)
  {
    return;
  }

  if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
  {
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
    {
      Subsystem->RemoveMappingContext(FireMappingContext);
    }
  }
}


void UTP_WeaponComponent::RotateBulletLeft()
{
  UE_LOG(LogTemplateCharacter, Error, TEXT("Rotacion bullet left"));
  TetrisPiece->RotateCounterClockwise();
}

void UTP_WeaponComponent::RotateBulletRight()
{
  UE_LOG(LogTemplateCharacter, Error, TEXT("Rotacion bullet right"));
  TetrisPiece->RotateClockwise();
}
