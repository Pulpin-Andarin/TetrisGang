#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledPork.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPoolCreated);

class AAirEnemy;
class AMeleEnemy;
class AEnemyProjectile;
class ATetrisGangProjectile;


UCLASS()
class TETRISGANG_API APooledPork : public AActor
{
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  APooledPork();

  //Classes to store in the pool and the quantity of them
  UPROPERTY(EditAnyWhere, Category = "Pool")
  TMap<TSubclassOf<AActor>, int32> ClassesToSpawn;

  //Contains the world location where the actors will be stored.
  UPROPERTY(VisibleAnyWhere, Category = "Pool")
  FVector PoolLocation;

  //UPROPERTY(VisibleAnyWhere, Category = "Pool")
  ////Multimap that stores all the spawns required, classified by class.
  //TMultiMap<TSubclassOf<AActor>, AActor*> Spawns;

  //Multimap that stores the index of each actor in the pool. Note: Not neccesary at the moment
  /*TMultiMap<TSubclassOf<AActor>, int32> IndexesSpawnedActors;*/
  //FPoolCreated PoolCreated;

  UPROPERTY()
  TArray<AAirEnemy*> AirEnemies;

  UPROPERTY()
  TArray<AMeleEnemy*> MeleEnemies;

  UPROPERTY()
  TArray<ATetrisGangProjectile*> PiecesProjectiles;

  int NumAirEnemies = 10;
  int NumMeleEnemies = 10;
  int NumPiecesProjectiles = 14;
  //UPROPERTY()
  //TArray<AEnemyProjectile*> EnemyProjectiles;


  UFUNCTION()
  void InitializePool();

  UFUNCTION()
  void ReturnToPool(AActor* ActorToPool);

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  //Function to obtain the first available actor in the pool of the specified class.
  AActor* GetNextActor(TSubclassOf<AActor> classToSpawn);

  //Function to obtain all the actors of the specified class.
  //TArray<AActor*> GetAllActors(TSubclassOf<AActor> classToSpawn);

  //int32 NumActiveActorsOfClass(TSubclassOf<AActor> Class);

  //bool CheckMaxActorsInScreenReached(TSubclassOf<AActor> Class, int32& NumToReachMax, int32 OverrideMax = -1);

};
