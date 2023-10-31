// Copyright Epic Games, Inc. All Rights Reserved.

#include "TetrisGangProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "../../Utils/Constantes.h"
#include "TetrisGang/Enemies/AirEnemy/AirEnemy.h"
#include "TetrisGang/Enemies/MeleEnemy/MeleEnemy.h"
#include "../../Managers/TetrisGangGameMode.h"
#include "../../PooledPork/PooledPork.h"
#include "TetrisGang/Pieces/TetrisPiece.h"
#include "Components/ChildActorComponent.h"

ATetrisGangProjectile::ATetrisGangProjectile()
{
  // Use a sphere as a simple collision representation
  CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
  CollisionComp->InitSphereRadius(5.0f);
  CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
  CollisionComp->OnComponentHit.AddDynamic(this, &ATetrisGangProjectile::OnHit);		// set up a notification for when this component hits something blocking

  // Players can't walk on it
  CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
  CollisionComp->CanCharacterStepUpOn = ECB_No;

  // Set as root component
  RootComponent = CollisionComp;

  ChildActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("TetrisPieceChildActor"));
  ChildActor->SetChildActorClass(ATetrisPiece::StaticClass());
  ChildActor->SetupAttachment(CollisionComp);

  // Use a ProjectileMovementComponent to govern this projectile's movement
  ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
  ProjectileMovement->UpdatedComponent = RootComponent;
  ProjectileMovement->InitialSpeed = 3000.f;
  ProjectileMovement->MaxSpeed = 3000.f;
  ProjectileMovement->bRotationFollowsVelocity = true;
  ProjectileMovement->bShouldBounce = true;
  ProjectileMovement->ProjectileGravityScale = 0.f;

  // Die after 3 seconds by default
  InitialLifeSpan = 0.f;
}

void ATetrisGangProjectile::BeginPlay()
{
  Super::BeginPlay();

  TetrisPieceChild = Cast<ATetrisPiece>(ChildActor->GetChildActor());
  //
  //TetrisPieceChild->PieceMesh->OnComponentHit.AddDynamic(this, &ATetrisGangProjectile::OnHit);		// set up a notification for when this component hits something blocking

  GameMode = Cast<ATetrisGangGameMode>(GetWorld()->GetAuthGameMode());
}

void ATetrisGangProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
  // Only add impulse and destroy projectile if we hit a physics
  if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) /*&& OtherComp->IsSimulatingPhysics()*/)
  {
    AAirEnemy* AirEnemy = Cast<AAirEnemy>(OtherActor);
    if (AirEnemy)
    {
      bool bPieceAndRotation = CheckPieceAndRotation(AirEnemy->Pieces, AirEnemy->PieceRotation);
      if (bPieceAndRotation)
      {
        GameMode->Pool->ReturnToPool(AirEnemy);
        //Destroy();
        GameMode->Pool->ReturnToPool(this);
      }
    }
    else {
      AMeleEnemy* MeleEnemy = Cast<AMeleEnemy>(OtherActor);
      if (MeleEnemy)
      {
        bool bPieceAndRotation = CheckPieceAndRotation(MeleEnemy->Pieces, MeleEnemy->PieceRotation);
        if (bPieceAndRotation)
        {
          GameMode->Pool->ReturnToPool(MeleEnemy);
          /* Destroy();*/
          GameMode->Pool->ReturnToPool(this);
        }
      }
    }
    //Deactivate();
    //Deactivate();
  }
}

bool ATetrisGangProjectile::CheckPieceAndRotation(TetrisPieceColor EnemyPieceColor, TetrisPieceRotation EnemyPieceRotation)
{
  if (EnemyPieceColor == TetrisPieceChild->PieceColor)
  {
    if (EnemyPieceColor == TetrisPieceColor::Red || EnemyPieceColor == TetrisPieceColor::Green || EnemyPieceColor == TetrisPieceColor::Cyan)
    {
      if ((EnemyPieceRotation == TetrisPieceRotation::Left || EnemyPieceRotation == TetrisPieceRotation::Right) && (TetrisPieceChild->PieceRotation == TetrisPieceRotation::Left || TetrisPieceChild->PieceRotation == TetrisPieceRotation::Right))
      {
        return true;
      }
      if ((EnemyPieceRotation == TetrisPieceRotation::Up || EnemyPieceRotation == TetrisPieceRotation::Down) && (TetrisPieceChild->PieceRotation == TetrisPieceRotation::Up || TetrisPieceChild->PieceRotation == TetrisPieceRotation::Down))
      {
        return true;
      }
    }
    else if (EnemyPieceColor == TetrisPieceColor::Yelow)
    {
      return true;
    }
    else if (EnemyPieceRotation == TetrisPieceChild->PieceRotation)
    {
      return true;
    }
  }

  return false;
}

void ATetrisGangProjectile::Reactivate()
{
  //GetWorld()->GetTimerManager().SetTimer(FireTimerHandler, this, &AProjectile::ReturnToPool, TimeToReturnProjectileToPool, false);

  SetActorTickEnabled(true);
  SetActorHiddenInGame(false);
  //bIsActive = true;

  if (IsValid(GetCollisionComp()))
  {
    GetCollisionComp()->SetNotifyRigidBodyCollision(true);
    GetCollisionComp()->SetGenerateOverlapEvents(true);
    GetCollisionComp()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  }

  //if (IsValid(TetrisPieceChild))
  //{
  //  TetrisPieceChild->PieceMesh->SetNotifyRigidBodyCollision(true);
  //  TetrisPieceChild->PieceMesh->SetGenerateOverlapEvents(true);
  //  //TetrisPieceChild->PieceMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  //  TetrisPieceChild->PieceMesh->SetCollisionEnabled(ECollisionEnabled::Ph);
  //}

  if (IsValid(GetProjectileMovement()))
  {
    GetProjectileMovement()->SetUpdatedComponent(RootComponent);
    GetProjectileMovement()->bSimulationEnabled = true;
    GetProjectileMovement()->SetComponentTickEnabled(true);
    GetProjectileMovement()->Activate();
  }

  ActivateReturnToPoolTimer();


  //FReactivate.Broadcast(this);
}

void ATetrisGangProjectile::ActivateReturnToPoolTimer()
{
  _timerDelegate.BindLambda([this]() {
    GameMode->Pool->ReturnToPool(this);
    });
  GetWorld()->GetTimerManager().SetTimer(ReturnTimerHandler, _timerDelegate, LifeSpan, false);
}

void ATetrisGangProjectile::Deactivate()
{

  //bIsActive = false;
  SetActorTickEnabled(false);
  SetActorHiddenInGame(true);

  if (IsValid(GetProjectileMovement()))
  {
    GetProjectileMovement()->SetUpdatedComponent(NULL);
    GetProjectileMovement()->Velocity = FVector(0.0, 0.0, 0.0);
    GetProjectileMovement()->UpdateComponentVelocity();
    GetProjectileMovement()->bSimulationEnabled = false;
    GetProjectileMovement()->SetComponentTickEnabled(false);
    GetProjectileMovement()->Deactivate();
    GetProjectileMovement()->ProjectileGravityScale = 0.f;
  }

  if (IsValid(GetCollisionComp()))
  {
    GetCollisionComp()->SetNotifyRigidBodyCollision(false);
    GetCollisionComp()->SetGenerateOverlapEvents(false);
    GetCollisionComp()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
  }
}