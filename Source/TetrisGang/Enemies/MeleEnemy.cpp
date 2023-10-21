// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleEnemy.h"
//#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

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
	bIsActive = true;

	SetActorTickEnabled(true);
	//if (GetController() == nullptr)
	//{
	//	AICharacterController->Possess(this);
	//}
	//AICharacterController->Reset();

	if (IsValid(MovementComponent))
	{
		MovementComponent->MaxWalkSpeed = InitialSpeed;
	}

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

