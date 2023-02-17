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

	UPROPERTY(EditAnywhere)
	float SpawnDistanceFromPlayer = 1000;

	UPROPERTY(EditAnywhere)
	float LevelTimerRate = 1;

	UPROPERTY(EditAnywhere)
	float BloobeSpawnTimerRate = 3;

	UPROPERTY(EditAnywhere)
	float BloobarSpawnTimerRate = 10;

	UPROPERTY(EditAnywhere)
	float BlooboxSpawnTimerRate = 30;

	UPROPERTY(EditAnywhere)
	float SpawnDistance = 500;
	
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

public:
	ALevel1();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
