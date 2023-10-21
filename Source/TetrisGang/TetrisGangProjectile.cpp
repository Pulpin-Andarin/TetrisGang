// Copyright Epic Games, Inc. All Rights Reserved.

#include "TetrisGangProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Constantes.h"

void ATetrisGangProjectile::BeginPlay()
{
  Super::BeginPlay();

  PieceMesh = Cast<UStaticMeshComponent>(GetComponentByClass(UStaticMeshComponent::StaticClass()));
}

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

  // Use a ProjectileMovementComponent to govern this projectile's movement
  ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
  ProjectileMovement->UpdatedComponent = CollisionComp;
  ProjectileMovement->InitialSpeed = 3000.f;
  ProjectileMovement->MaxSpeed = 3000.f;
  ProjectileMovement->bRotationFollowsVelocity = true;
  ProjectileMovement->bShouldBounce = true;
  ProjectileMovement->ProjectileGravityScale = 0.f;

  // Die after 3 seconds by default
  InitialLifeSpan = 3.0f;
}

void ATetrisGangProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
  // Only add impulse and destroy projectile if we hit a physics
  if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
  {
    OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

    Deactivate();
  }
}

void ATetrisGangProjectile::UpdateMesh(UStaticMesh* NewMesh)
{
  PieceMesh->SetStaticMesh(NewMesh);
}

void ATetrisGangProjectile::Rotate()
{
  switch (Rotation)
  {
  case Rotations::Up:
    PieceMesh->SetRelativeRotation(FRotator(0.0, 0.0, 0.0));
    break;
  case Rotations::Right:
    PieceMesh->SetRelativeRotation(FRotator(0.0, 0.0, 90.0));
    break;
  case Rotations::Down:
    PieceMesh->SetRelativeRotation(FRotator(0.0, 0.0, 180.0));
    break;
  case Rotations::Left:
    PieceMesh->SetRelativeRotation(FRotator(0.0, 0.0, -90.0));
    break;
  }
}


void ATetrisGangProjectile::Deactivate()
{

  //bIsActive = false;
  SetActorTickEnabled(false);
  SetActorHiddenInGame(true);

  /*TargetMode = EProjectileTargetMode::Default;

  FiringTurret = false;*/

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

  if (IsValid(PieceMesh))
  {
    PieceMesh->Deactivate();
  }

  // Return Pool

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

  if (IsValid(GetProjectileMovement()))
  {
    GetProjectileMovement()->SetUpdatedComponent(GetCollisionComp());
    GetProjectileMovement()->bSimulationEnabled = true;
    GetProjectileMovement()->SetComponentTickEnabled(true);
    GetProjectileMovement()->Activate();
    //if (bIsParabolicProjectile)
    //{
    //  ProjectileMovementComponent->ProjectileGravityScale = 1.f;
    //}
  }

  if (IsValid(PieceMesh))
  {
    PieceMesh->Activate(true);
  }


  //FReactivate.Broadcast(this);
}