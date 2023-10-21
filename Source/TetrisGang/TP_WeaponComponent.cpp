// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "TetrisGangCharacter.h"
#include "TetrisGangProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);

}


void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			ATetrisGangProjectile* ActualProjectile = World->SpawnActor<ATetrisGangProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			ActualProjectile->Rotation = ActualRotation; 
			ActualProjectile->Piece = ActualPiece;
			ActualProjectile->Rotate();
			ActualProjectile->UpdateMesh(ActualMesh);
		}

		// Try and play the sound if specified
		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
		}

		// Try and play a firing animation if specified
		if (FireAnimation != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
			if (AnimInstance != nullptr)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}

		ActualRotation = Rotations::Up;
	}
}


void UTP_WeaponComponent::AttachWeapon(ATetrisGangCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	// Check that the character is valid, and has no rifle yet
	if (Character == nullptr || Character->GetHasRifle())
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);

			// Rotate Bullet
			EnhancedInputComponent->BindAction(RotateBulletLeftAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::RotateBulletLeft);

			// Rotate Bullet
			EnhancedInputComponent->BindAction(RotateBulletRightAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::RotateBulletRight);

		}
	}

	CreateRandomProjectile();
}

void UTP_WeaponComponent::CreateRandomProjectile()
{
	ActualPiece = Constantes::GetRandomPiece();
	ActualRotation = Rotations::Up;

	switch (ActualPiece)
	{
		case Pieces::Yelow:
			ActualMesh = AvailablePiecesMeshes[0];
			break;
		case Pieces::Cyan:
			ActualMesh = AvailablePiecesMeshes[1];
			break;
		case Pieces::Green:
			ActualMesh = AvailablePiecesMeshes[2];
			break;
		case Pieces::Red:
			ActualMesh = AvailablePiecesMeshes[3];
			break;
		case Pieces::Orange:
			ActualMesh = AvailablePiecesMeshes[4];
			break;
		case Pieces::Blue:
			ActualMesh = AvailablePiecesMeshes[5];
			break;
		case Pieces::Purple:
			ActualMesh = AvailablePiecesMeshes[6];
			break;
		default:
			break;
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}


void UTP_WeaponComponent::RotateBulletLeft()
{
	UE_LOG(LogTemplateCharacter, Error, TEXT("Rotacion bullet left"));

	switch (ActualRotation) {
		case Rotations::Up: 
			ActualRotation = Rotations::Left;
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: left"));
			break;
		case Rotations::Left:
			ActualRotation = Rotations::Down;
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: Down"));
			break;
		case Rotations::Down:
			ActualRotation = Rotations::Right;
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: Right"));
			break;
		case Rotations::Right:
			ActualRotation = Rotations::Up;
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: Up"));
			break;
	}
}

void UTP_WeaponComponent::RotateBulletRight()
{
	UE_LOG(LogTemplateCharacter, Error, TEXT("Rotacion bullet right"));

	switch (ActualRotation) {
		case Rotations::Up:
			ActualRotation = Rotations::Right;
			StaticProjectile->SetRelativeRotation(FRotator(0.0, 0.0, 90.0));
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: Right"));
			break;
		case Rotations::Right:
			ActualRotation = Rotations::Down;
			StaticProjectile->SetRelativeRotation(FRotator(0.0, 0.0, 90.0));
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: Down"));
			break;
		case Rotations::Down:
			ActualRotation = Rotations::Left;
			StaticProjectile->SetRelativeRotation(FRotator(0.0, 0.0, 90.0));
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: left"));
			break;
		case Rotations::Left:
			ActualRotation = Rotations::Up;
			StaticProjectile->SetRelativeRotation(FRotator(0.0, 0.0, 90.0));
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: Up"));
			break;
	}
}