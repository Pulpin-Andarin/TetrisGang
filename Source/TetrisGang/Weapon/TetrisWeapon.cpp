// Fill out your copyright notice in the Description page of Project Settings.


#include "TetrisWeapon.h"
#include "TetrisGang/Pieces/TetrisPiece.h"

// Sets default values
ATetrisWeapon::ATetrisWeapon()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  //TetrisPiece = CreateDefaultSubobject<UTetrisPiece>(FName("TetrisPiece"));
  //TetrisPiece->RegisterComponent();
}

// Called when the game starts or when spawned
void ATetrisWeapon::BeginPlay()
{
  Super::BeginPlay();

}

// Called every frame
void ATetrisWeapon::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

}

