// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn.h"
#include "../TetrisGangGameMode.h"
#include "../PooledPork/PooledPork.h"
#include "../Enemies/AirEnemy.h"
#include "../Enemies/MeleEnemy.h"

// Sets default values
ASpawn::ASpawn()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawn::BeginPlay()
{
  Super::BeginPlay();

  TetrisGameMode = Cast<ATetrisGangGameMode>(GetWorld()->GetAuthGameMode());


}

// Called every frame
void ASpawn::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

void ASpawn::SpawnEnemy()
{
  AActor* ActorAir = TetrisGameMode->Pool->GetNextActor(AAirEnemy::StaticClass());
  if (ActorAir)
  {
    AAirEnemy* AirEnemy = Cast<AAirEnemy>(ActorAir);
    AirEnemy->SetActorLocation(SpawnLocation);
    AirEnemy->Reactivate();
  }

  AActor* ActorMele = TetrisGameMode->Pool->GetNextActor(AMeleEnemy::StaticClass());
  if (ActorMele)
  {
    AMeleEnemy* MeleEnemy = Cast<AMeleEnemy>(ActorMele);
    MeleEnemy->SetActorLocation(SpawnLocation);
    MeleEnemy->Reactivate();
  }
}

void ASpawn::Initialize() {

  SpawnLocation = GetActorLocation();
  GetWorld()->GetTimerManager().SetTimer(
    FuzeTimerHandle, // handle to cancel timer at a later time
    this, // the owning object
    &ASpawn::SpawnEnemy, // function to call on elapsed
    CooldownBetweenSpawns, // float delay until elapsed
    true, 5.f); // looping?

}
