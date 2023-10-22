// Fill out your copyright notice in the Description page of Project Settings.


#include "AirEnemy.h"
#include <TetrisGang/TetrisGangGameMode.h>
#include "AIController.h"
#include "BrainComponent.h"

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
  ATetrisGangGameMode* GameMode = Cast<ATetrisGangGameMode>(GetWorld()->GetAuthGameMode());
  AirEnemyDeath.AddDynamic(GameMode, &ATetrisGangGameMode::UpdateEnemyCounter);
  AIController = Cast<AAIController>(GetController());

  AirMesh = Cast<UStaticMeshComponent>(FindComponentByTag<UStaticMeshComponent>(TEXT("BoxMesh")));
  BoxCollision = Cast<UBoxComponent>(FindComponentByTag<UBoxComponent>(FName(TEXT("BoxColl"))));
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

  SetActorTickEnabled(true);

  //if (GetController() == nullptr)
  //{
  //  AIController->Possess(this);
  //}


  //if (IsValid(MovementComponent))
  //{
  //  MovementComponent->MaxWalkSpeed = InitialSpeed;
  //}

  if (IsValid(BoxCollision))
  {
    BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxCollision->SetCanEverAffectNavigation(true);
  }

  if (IsValid(AirMesh))
  {
    //AirMesh->ResetAnimInstanceDynamics(ETeleportType::ResetPhysics);
    AirMesh->Activate(true);
    AirMesh->SetVisibility(true);
  }


  //if (IsValid(AIController))
  //{
  //  AIController->Reset();
  //  AIController->GetBrainComponent()->Activate();
  //  AIController->GetBrainComponent()->RestartLogic();
  //}

  //GetCharacterMovement()->GravityScale = 1.f;

}

void AAirEnemy::Deactivate()
{
  SetActorTickEnabled(false);
  /*if (IsValid(GetMesh()))
  {
    GetMesh()->ResetAnimInstanceDynamics(ETeleportType::TeleportPhysics);
    GetMesh()->SetVisibility(false);
    GetMesh()->Deactivate();
  }*/

 /* if (IsValid(GetController()))
  {
    if (GetController() != nullptr)
    {
      GetController()->GetBrainComponent()->StopLogic(FString("Go to pool"));
      GetController()->GetBrainComponent()->Deactivate();
      GetController()->UnPossess();
    }
  }*/
  //ReturnToPool//
  // 
  //GetCharacterMovement()->GravityScale = 0.f;
}

