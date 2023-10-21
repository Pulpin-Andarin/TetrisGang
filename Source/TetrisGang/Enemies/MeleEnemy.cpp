// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleEnemy.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "BrainComponent.h"
#include <TetrisGang/TetrisGangGameMode.h>

// Sets default values
AMeleEnemy::AMeleEnemy()
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMeleEnemy::BeginPlay()
{
  Super::BeginPlay();

  //AICharacterController = Cast<AAIController>(GetController());

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

  ATetrisGangGameMode* GameMode = Cast<ATetrisGangGameMode>(GetWorld()->GetAuthGameMode());
  MeleEnemyDeath.AddDynamic(GameMode, &ATetrisGangGameMode::UpdateEnemyCounter);
  AICharacterController = Cast<AAIController>(GetController());

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

  SetActorTickEnabled(true);

  if (GetController() == nullptr)
  {
    AICharacterController->Possess(this);
  }

  AICharacterController->Reset();

  //if (IsValid(MovementComponent))
  //{
  //  MovementComponent->MaxWalkSpeed = InitialSpeed;
  //}

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

    AICharacterController->GetBrainComponent()->Activate();
    AICharacterController->GetBrainComponent()->RestartLogic();
  }

  GetCharacterMovement()->GravityScale = 1.f;

}
void AMeleEnemy::Deactivate()
{
  SetActorTickEnabled(false);
  if (IsValid(GetMesh()))
  {
    GetMesh()->ResetAnimInstanceDynamics(ETeleportType::TeleportPhysics);
    GetMesh()->SetVisibility(false);
    GetMesh()->Deactivate();
  }

  if (IsValid(AICharacterController))
  {
    if (AICharacterController != nullptr)
    {
      AICharacterController->GetBrainComponent()->StopLogic(FString("Go to pool"));
      AICharacterController->GetBrainComponent()->Deactivate();
      AICharacterController->UnPossess();
    }
  }

  GetCharacterMovement()->GravityScale = 0.f;
}
//
//void AMeleEnemy::Activate()
//{
//}

void AMeleEnemy::EnemyDeath()
{
  MeleEnemyDeath.Broadcast();
}


// Called to bind functionality to input
void AMeleEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
  if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
  {
    /*if (OtherActor->IsA<ATetrisPiece>())
    {
      EmunPiece Piece	 = Cast<ATetrisPiece>(OtherActor)->GetPiece();
      EmunRotation Rotarion = Cast<ATetrisPiece>(OtherActor)->GetRotation();
      if (Piece == this->Piece && Rotation == this->Rotation)
      {
        Died();
      }
    }*/
  }
}

