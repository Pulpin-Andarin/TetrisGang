// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleEnemy.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "BrainComponent.h"
#include "Components/BillboardComponent.h"
#include <TetrisGang/Managers/TetrisGangGameMode.h>
#include <TetrisGang/Pieces/TetrisPiece.h>
#include "Components/ChildActorComponent.h"
#include "TetrisGang/PooledPork/PooledPork.h"

// Sets default values
AMeleEnemy::AMeleEnemy()
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  //StaticProjectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticProjectileComponent"));
  //StaticProjectile->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMeleEnemy::BeginPlay()
{
  Super::BeginPlay();

  AICharacterController = Cast<AAIController>(GetController());
  CapsuleComponentCollision = Cast<UCapsuleComponent>(GetComponentByClass(UCapsuleComponent::StaticClass()));
  MovementComponent = FindComponentByClass<UCharacterMovementComponent>();

  if (!MovementComponent)
  {
    UE_LOG(LogTemp, Warning, TEXT("MovementComponent no encontrada"));
  }
  else
  {
    InitialSpeed = MovementComponent->MaxWalkSpeed;
  }

  GameMode = Cast<ATetrisGangGameMode>(GetWorld()->GetAuthGameMode());
  MeleEnemyDeath.AddDynamic(GameMode, &ATetrisGangGameMode::UpdateEnemyCounter);

  //BillboardComponent = Cast<UBillboardComponent>(FindComponentByTag<UBillboardComponent>(FName(TEXT("billboardPiece"))));

  UChildActorComponent& ChildActor = *Cast<UChildActorComponent>(FindComponentByClass(UChildActorComponent::StaticClass()));

  TetrisChestPiece = Cast<ATetrisPiece>(ChildActor.GetChildActor());
}

// Called every frame
void AMeleEnemy::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMeleEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMeleEnemy::Reactivate()
{
  IEnemyBaseInterface::Reactivate();

  SetActorTickEnabled(true);

  if (GetController() == nullptr)
  {
    AICharacterController->Possess(this);
  }

  if (IsValid(CapsuleComponentCollision))
  {
    CapsuleComponentCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CapsuleComponentCollision->SetCanEverAffectNavigation(true);
  }

  if (IsValid(GetMesh()))
  {
    GetMesh()->ResetAnimInstanceDynamics(ETeleportType::ResetPhysics);
    GetMesh()->Activate(true);
    GetMesh()->SetVisibility(true);
  }


  if (IsValid(AICharacterController))
  {
    AICharacterController->Reset();
    AICharacterController->GetBrainComponent()->Activate();
    AICharacterController->GetBrainComponent()->RestartLogic();
  }

  GetCharacterMovement()->GravityScale = 1.f;
}


void AMeleEnemy::Deactivate()
{
  IEnemyBaseInterface::Deactivate();

  SetActorTickEnabled(false);
  if (IsValid(GetMesh()))
  {
    GetMesh()->ResetAnimInstanceDynamics(ETeleportType::TeleportPhysics);
    GetMesh()->SetVisibility(false);
    GetMesh()->Deactivate();
  }

  if (IsValid(AICharacterController))
  {
    if (GetController() != nullptr)
    {
      AICharacterController->GetBrainComponent()->StopLogic(FString("Go to pool"));
      AICharacterController->GetBrainComponent()->Deactivate();
      AICharacterController->UnPossess();
    }
  }

  GetCharacterMovement()->GravityScale = 0.f;

}

void AMeleEnemy::ReturnToPool()
{
  IEnemyBaseInterface::ReturnToPool();
  SetActorLocation(GameMode->Pool->PoolLocation);
  GameMode->Pool->MeleEnemies.Push(this);
}


void AMeleEnemy::EnemyDeath()
{
  MeleEnemyDeath.Broadcast();
}


