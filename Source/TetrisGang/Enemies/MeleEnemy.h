// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Constantes.h"
#include "MeleEnemy.generated.h"

class UWalkToComponent;
class UCapsuleComponent;
class UCharacterMovementComponent;


UCLASS()
class TETRISGANG_API AMeleEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeleEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
		void Reactivate();

	bool bIsActive;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CapsuleComponentCollision;

	UPROPERTY(VisibleAnywhere)
		UCharacterMovementComponent* MovementComponent;

	/*UPROPERTY()
		AAIController* AICharacterController;*/

	float InitialSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere)
		Rotations rotation;

	UPROPERTY(VisibleAnywhere)
		Pieces Pieces;
};
