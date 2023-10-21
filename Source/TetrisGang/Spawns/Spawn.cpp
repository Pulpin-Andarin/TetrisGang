// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawn.h"

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

  GetWorld()->GetTimerManager().SetTimer(
    FuzeTimerHandle, // handle to cancel timer at a later time
    this, // the owning object
    &ASpawn::SpawnEnemy, // function to call on elapsed
    CooldownBetweenSpawns, // float delay until elapsed
    true, 0.2f); // looping?
}

// Called every frame
void ASpawn::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

void ASpawn::SpawnEnemy()
{
  // spawn
  // GetEnemy from pool
}
