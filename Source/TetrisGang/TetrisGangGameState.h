// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TetrisGangGameState.generated.h"

/**
 * 
 */
UCLASS()
class TETRISGANG_API ATetrisGangGameState : public AGameState
{
	GENERATED_BODY()


public:

	UPROPERTY(BlueprintReadWrite)
		TMap<FName, int> Laderboard;
		
	UFUNCTION(BlueprintCallable)
		void AddLaderboardEntry(FName playerName,int score);
	
};
