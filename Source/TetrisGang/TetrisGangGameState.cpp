// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisGangGameState.h"
#include "GameFramework/PlayerState.h"


void ATetrisGangGameState::AddLaderboardEntry(FName playerName, int score)
{
	Laderboard.Add(playerName, score);
}