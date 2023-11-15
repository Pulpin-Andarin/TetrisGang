// Fill out your copyright notice in the Description page of Project Settings.


#include "AirEnemy.h"
#include <TetrisGang/Managers/TetrisGangGameMode.h>
#include "AIController.h"
#include "BrainComponent.h"
#include "TetrisGang/Utils/Constantes.h"
#include <TetrisGang/Pieces/TetrisPiece.h>
#include "Components/ChildActorComponent.h"
#include "TetrisGang/PooledPork/PooledPork.h"

// Sets default values
AAirEnemy::AAirEnemy()
{
  // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAirEnemy::BeginPlay()
{
  Super::BeginPlay();
  GameMode = Cast<ATetrisGangGameMode>(GetWorld()->GetAuthGameMode());
  AirEnemyDeath.AddDynamic(GameMode, &ATetrisGangGameMode::UpdateEnemyCounter);

  UChildActorComponent& ChildActor = *Cast<UChildActorComponent>(FindComponentByClass(UChildActorComponent::StaticClass()));
  TetrisChestPiece = Cast<ATetrisPiece>(ChildActor.GetChildActor());
}

// Called every frame
void AAirEnemy::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAirEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAirEnemy::EnemyDeath()
{
  AirEnemyDeath.Broadcast();
}


void AAirEnemy::Reactivate()
{
  IEnemyBaseInterface::Reactivate();
  SetActorTickEnabled(true);
  if (GetController() == nullptr)
  {
    AIController->Possess(this);
  }

  if (IsValid(BoxCollision))
  {
    BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxCollision->SetCanEverAffectNavigation(true);
  }

  if (IsValid(AirMesh))
  {
    AirMesh->Activate(true);
    AirMesh->SetVisibility(true);
  }


  if (IsValid(AIController))
  {
    AIController->Reset();
    AIController->GetBrainComponent()->Activate();
    AIController->GetBrainComponent()->RestartLogic();
  }

}

void AAirEnemy::Deactivate()
{
  IEnemyBaseInterface::Deactivate();

  SetActorTickEnabled(false);
  if (IsValid(AirMesh))
  {
    AirMesh->SetVisibility(false);
    AirMesh->Deactivate();
  }

  if (IsValid(AIController))
  {
    if (GetController() != nullptr)
    {
      AIController->GetBrainComponent()->StopLogic(FString("Go to pool"));
      AIController->GetBrainComponent()->Deactivate();
      AIController->UnPossess();
    }
  }
}

void AAirEnemy::ReturnToPool()
{
  IEnemyBaseInterface::ReturnToPool();
  SetActorLocation(GameMode->Pool->PoolLocation);
  GameMode->Pool->AirEnemies.Push(this);
}
