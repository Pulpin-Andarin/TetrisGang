// Fill out your copyright notice in the Description page of Project Settings.


#include "AirEnemy.h"
#include <TetrisGang/Managers/TetrisGangGameMode.h>
#include "AIController.h"
#include "BrainComponent.h"
#include "TetrisGang/Utils/Constantes.h"
#include "Components/BillboardComponent.h"

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
  //AIController = Cast<AAIController>(GetController());

  //AirMesh = Cast<UStaticMeshComponent>(FindComponentByTag<UStaticMeshComponent>(TEXT("BoxMesh")));
  //BoxCollision = Cast<UBoxComponent>(FindComponentByTag<UBoxComponent>(FName(TEXT("BoxColl"))));
  BillboardComponent = Cast<UBillboardComponent>(FindComponentByTag<UBillboardComponent>(FName(TEXT("billboardPiece"))));

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

  //SetActorTickEnabled(true);

  if (GetController() == nullptr)
  {
    AIController->Possess(this);
  }


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


  if (IsValid(AIController))
  {
    AIController->Reset();
    AIController->GetBrainComponent()->Activate();
    AIController->GetBrainComponent()->RestartLogic();
  }

  //GetCharacterMovement()->GravityScale = 1.f;
  Pieces = Constantes::GetRandomPiece();

  PieceRotation = Constantes::GetRandomRotation();

  SelectPieceMesh();
}

void AAirEnemy::Deactivate()
{
  SetActorTickEnabled(false);
  if (IsValid(AirMesh))
  {
    //AirMesh->ResetAnimInstanceDynamics(ETeleportType::TeleportPhysics);
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

  //ReturnToPool//

  //GetCharacterMovement()->GravityScale = 0.f;
}


void AAirEnemy::SelectPieceMesh()
{
  int position = 0;
  switch (PieceRotation) {
  case TetrisPieceRotation::Up:
    position = 0;
    break;
  case TetrisPieceRotation::Right:
    position = 1;
    break;
  case TetrisPieceRotation::Down:
    position = 2;
    break;
  case TetrisPieceRotation::Left:
    position = 3;
    break;
  }

  switch (Pieces)
  {
  case TetrisPieceColor::Yelow:
    BillboardComponent->SetSprite(YellowTextures[position]);
    break;
  case TetrisPieceColor::Cyan:
    BillboardComponent->SetSprite(CyamTextures[position]);
    break;
  case TetrisPieceColor::Green:
    BillboardComponent->SetSprite(GreenTextures[position]);
    break;
  case TetrisPieceColor::Red:
    BillboardComponent->SetSprite(RedTextures[position]);
    break;
  case TetrisPieceColor::Orange:
    BillboardComponent->SetSprite(OrangeTextures[position]);
    break;
  case TetrisPieceColor::Blue:
    BillboardComponent->SetSprite(BlueTextures[position]);
    break;
  case TetrisPieceColor::Purple:
    BillboardComponent->SetSprite(PurpleTextures[position]);
    break;
  default:
    break;
  }

  BillboardComponent->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
}

