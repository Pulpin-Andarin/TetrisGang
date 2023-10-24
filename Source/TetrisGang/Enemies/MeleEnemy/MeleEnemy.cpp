// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleEnemy.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "BrainComponent.h"
#include "Components/BillboardComponent.h"
#include <TetrisGang/Managers/TetrisGangGameMode.h>


// Sets default values
AMeleEnemy::AMeleEnemy()
{
  // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

  StaticProjectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticProjectileComponent"));
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

  ATetrisGangGameMode* GameMode = Cast<ATetrisGangGameMode>(GetWorld()->GetAuthGameMode());
  MeleEnemyDeath.AddDynamic(GameMode, &ATetrisGangGameMode::UpdateEnemyCounter);

  BillboardComponent = Cast<UBillboardComponent>(FindComponentByTag<UBillboardComponent>(FName(TEXT("billboardPiece"))));

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
    AICharacterController->Reset();
    AICharacterController->GetBrainComponent()->Activate();
    AICharacterController->GetBrainComponent()->RestartLogic();
  }

  GetCharacterMovement()->GravityScale = 1.f;

  Pieces = Constantes::GetRandomPiece();

  PieceRotation = Constantes::GetRandomRotation();

  SelectPieceMesh();
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
    if (GetController() != nullptr)
    {
      AICharacterController->GetBrainComponent()->StopLogic(FString("Go to pool"));
      AICharacterController->GetBrainComponent()->Deactivate();
      AICharacterController->UnPossess();
    }
  }

  GetCharacterMovement()->GravityScale = 0.f;
  //ReturnToPool//
  //SetActorLocation();
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

void AMeleEnemy::SelectPieceMesh()
{
  int position = 0;
  switch (PieceRotation) {
  case Rotations::Up:
    position = 0;
    break;
  case Rotations::Right:
    position = 1;
    break;
  case Rotations::Down:
    position = 2;
    break;
  case Rotations::Left:
    position = 3;
    break;
  }

  switch (Pieces)
  {
  case Pieces::Yelow:
    BillboardComponent->SetSprite(YellowTextures[position]);
    break;
  case Pieces::Cyan:
    BillboardComponent->SetSprite(CyamTextures[position]);
    break;
  case Pieces::Green:
    BillboardComponent->SetSprite(GreenTextures[position]);
    break;
  case Pieces::Red:
    BillboardComponent->SetSprite(RedTextures[position]);
    break;
  case Pieces::Orange:
    BillboardComponent->SetSprite(OrangeTextures[position]);
    break;
  case Pieces::Blue:
    BillboardComponent->SetSprite(BlueTextures[position]);
    break;
  case Pieces::Purple:
    BillboardComponent->SetSprite(PurpleTextures[position]);
    break;
  default:
    break;
  }

  BillboardComponent->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
}

