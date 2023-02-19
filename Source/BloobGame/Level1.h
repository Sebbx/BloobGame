// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Engine/LevelScriptActor.h"
#include "Level1.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBGAME_API ALevel1 : public ALevelScriptActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> BloobeClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> BloobarClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> BlooboxClass;

	UPROPERTY(EditAnywhere, Category = Spawning)
	float LevelTimerRate = 1;

	UPROPERTY(EditAnywhere, Category = Spawning)
	float BloobeSpawnTimerRate = 3;

	UPROPERTY(EditAnywhere, Category = Spawning)
	float BloobeSpawnRateMultiplayer = .95;

	UPROPERTY(EditAnywhere, Category = Spawning)
	float BloobarSpawnTimerRate = 10;
	
	UPROPERTY(EditAnywhere, Category = Spawning)
	float BloobarSpawnRateMultiplayer = .95;

	UPROPERTY(EditAnywhere, Category = Spawning)
	int BloobarMinuteActivation = 5;
	
	UPROPERTY(EditAnywhere, Category = Spawning)
	float BlooboxSpawnTimerRate = 30;

	UPROPERTY(EditAnywhere, Category = Spawning)
	float BlooboxSpawnRateMultiplayer = .95;

	UPROPERTY(EditAnywhere, Category = Spawning)
	int BlooboxMinuteActivation = 10;
	
	UPROPERTY(EditAnywhere, Category = Spawning)
	float SpawnDistance = 500;
		
	UPROPERTY(EditAnywhere, Category = Spawning)
	float InitialTimeDilation = 1;
	
	int Minutes = 0;
	int Seconds = 0;
	
	FTimerHandle LevelTimerHandle;
	FTimerHandle BloobeSpawnTimerHandle;
	FTimerHandle BloobarSpawnTimerHandle;
	FTimerHandle BlooboxSpawnTimerHandle;

	class APlayerPawn* PlayerRef;

	void StartLevelTimer();
	void StartBloobeSpawnTimer();
	void StartBloobarSpawnTimer();
	void StartBlooboxSpawnTimer();
	void SpawnEnemy(TSubclassOf<AEnemy> EnemyBP);

	UPROPERTY(EditAnywhere)
	bool CanSpawn = true;

public:
	ALevel1();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
