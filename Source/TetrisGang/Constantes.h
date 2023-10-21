// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"



UENUM(BlueprintType)
enum class Rotations : uint8{
	Up UMETA(DisplayName="Up"),
	Right UMETA(DisplayName = "Right"),
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName="Left")
};

UENUM(BlueprintType)
enum class Pieces : uint8 {
	Yelow UMETA(DisplayName="Yelow"),
	Cyan UMETA(DisplayName="Cyan"),
	Green UMETA(DisplayName="Green"),
	Red UMETA(DisplayName="Red"),
	Orange UMETA(DisplayName="Orange"),
	Blue UMETA(DisplayName="Blue"),
	Purple UMETA(DisplayName="Purple")
};

/**
 * 
 */
class TETRISGANG_API Constantes
{
public:

};
