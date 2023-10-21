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
			World->SpawnActor<ATetrisGangProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	/*if (IsValid(ActualProjectile))
	{
		CreateProjectile();
		ActualProjectile->Fire();
	}
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}*/
	
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

void UTP_WeaponComponent::CreateProjectile() {
	// Try and fire a projectile
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
			ActualProjectile = World->SpawnActor<ATetrisGangProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
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

	//CreateProjectile();
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

	if (IsValid(ActualProjectile))
	{
		ActualProjectile->Rotate(ActualRotation);
	}
}

void UTP_WeaponComponent::RotateBulletRight()
{
	UE_LOG(LogTemplateCharacter, Error, TEXT("Rotacion bullet right"));

	switch (ActualRotation) {
		case Rotations::Up:
			ActualRotation = Rotations::Right;
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: Right"));
			break;
		case Rotations::Right:
			ActualRotation = Rotations::Down;
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: Down"));
			break;
		case Rotations::Down:
			ActualRotation = Rotations::Left;
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: left"));
			break;
		case Rotations::Left:
			ActualRotation = Rotations::Up;
			UE_LOG(LogTemplateCharacter, Error, TEXT("Actual Rotacion: Up"));
			break;
	}

	if (IsValid(ActualProjectile))
	{
		ActualProjectile->Rotate(ActualRotation);
	}
}