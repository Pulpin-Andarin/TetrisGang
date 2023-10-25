// Fill out your copyright notice in the Description page of Project Settings.


#include "PooledPork.h"
#include "Kismet/GameplayStatics.h"
#include <TetrisGang/Enemies/MeleEnemy/MeleEnemy.h>
#include <TetrisGang/Enemies/AirEnemy/AirEnemy.h>
#include <TetrisGang/Enemies/Projectiles/EnemyProjectile.h>
#include <TetrisGang/Enemies/AirEnemy/AirController.h>
#include "../Weapon/Projectile/TetrisGangProjectile.h"

// Sets default values
APooledPork::APooledPork()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

void APooledPork::InitializePool()
{
  //Sets the pool location
  PoolLocation = GetActorLocation();

  FActorSpawnParameters SpawnInfo;
  SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
  // Create Pool
  for (int i = 0; i < NumMeleEnemies; i++)
  {
    AMeleEnemy* AM = GetWorld()->SpawnActor<AMeleEnemy>(MeleEnemyClass, PoolLocation, FRotator().ZeroRotator, SpawnInfo);
    AAIController* Aic = GetWorld()->SpawnActor<AAIController>(MeleEnemyControllerClass, PoolLocation, FRotator().ZeroRotator, SpawnInfo);
    AM->AICharacterController = Aic;
    MeleEnemies.Add(AM);
  }
  // Create Pool
  for (int i = 0; i < NumPiecesProjectiles; i++)
  {
    ATetrisGangProjectile* AM = GetWorld()->SpawnActor<ATetrisGangProjectile>(TetrisGangProjectileClass, PoolLocation, FRotator().ZeroRotator, SpawnInfo);
    AM->Deactivate();
    PiecesProjectiles.Add(AM);
  }
  // Create Pool
  for (int i = 0; i < NumAirEnemies; i++)
  {
    AAirEnemy* AM = GetWorld()->SpawnActor<AAirEnemy>(AirEnemyClass, PoolLocation, FRotator().ZeroRotator, SpawnInfo);
    AAIController* Aic = GetWorld()->SpawnActor<AAIController>(AirEnemyControllerClass, PoolLocation, FRotator().ZeroRotator, SpawnInfo);
    AM->AIController = Aic;

    AM->Deactivate();
    AirEnemies.Add(AM);
  }

  PoolCreated.Broadcast();
}

// Called when the game starts or when spawned
void APooledPork::BeginPlay()
{
  Super::BeginPlay();
  //SuscribeToReactivateDelegate();
}



// Called every frame
void APooledPork::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}


AActor* APooledPork::GetNextActor(TSubclassOf<AActor> ClassToSpawn)
{
  if (ClassToSpawn == AAirEnemy::StaticClass())
  {
    if (AirEnemies.Num() > 0)
    {
      AAirEnemy* AirEnemy = AirEnemies.Pop();
      AirEnemy->Reactivate();
      return AirEnemy;
    }
  }
  else if (ClassToSpawn == AMeleEnemy::StaticClass())
  {
    if (MeleEnemies.Num() > 0)
    {
      AMeleEnemy* MeleEnemy = MeleEnemies.Pop();
      MeleEnemy->Reactivate();
      return MeleEnemy;
    }
  }
  else if (ClassToSpawn->IsChildOf(ATetrisGangProjectile::StaticClass()))
  {
    if (PiecesProjectiles.Num() > 0)
    {
      ATetrisGangProjectile* PiecesProjectile = PiecesProjectiles.Pop();
        PiecesProjectile->Reactivate();
        return PiecesProjectile;
    }
  }

  return nullptr;
}

void APooledPork::ReturnToPool(AActor* ActorToPool)
{
  if (Cast<AAirEnemy>(ActorToPool))
  {
    AAirEnemy* AirEnemy = Cast<AAirEnemy>(ActorToPool);
    AirEnemy->Deactivate();
    AirEnemy->SetActorLocation(PoolLocation);
    AirEnemies.Push(AirEnemy);
  }
  else if ((Cast<AMeleEnemy>(ActorToPool)))
  {
    AMeleEnemy* MeleEnemy = Cast<AMeleEnemy>(ActorToPool);
    MeleEnemy->Deactivate();
    MeleEnemy->SetActorLocation(PoolLocation);
    MeleEnemies.Push(MeleEnemy);
  }
  else if ((Cast<ATetrisGangProjectile>(ActorToPool)))
  {
    ATetrisGangProjectile* Projectile = Cast<ATetrisGangProjectile>(ActorToPool);
    Projectile->Deactivate();
    Projectile->SetActorLocation(PoolLocation);
    PiecesProjectiles.Push(Projectile);

    //PiecesProjectiles.Push((Cast<ATetrisGangProjectile>(ActorToPool)));
  }

}

