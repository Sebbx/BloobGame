// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1.h"

#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"


ALevel1::ALevel1()
{
	//PrimaryActorTick.bCanEverTick = true;
}

void ALevel1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ALevel1::BeginPlay()
{
	PlayerRef = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	PlayerRef->MinutesRef = &Minutes;
	PlayerRef->SecondsRef = &Seconds;
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(LevelTimerHandle, this, &ALevel1::StartLevelTimer, LevelTimerRate, true, 1);
	GetWorld()->GetTimerManager().SetTimer(BloobeSpawnTimerHandle, this, &ALevel1::StartBloobeSpawnTimer, BloobeSpawnTimerRate, true, 0);
	GetWorld()->GetTimerManager().SetTimer(BloobarSpawnTimerHandle, this, &ALevel1::StartBloobarSpawnTimer, BloobarSpawnTimerRate, true, BloobarSpawnTimerRate);
	GetWorld()->GetTimerManager().SetTimer(BlooboxSpawnTimerHandle, this, &ALevel1::StartBlooboxSpawnTimer, BlooboxSpawnTimerRate, true, BlooboxSpawnTimerRate);
}

void ALevel1::StartLevelTimer()
{
	Seconds++;
	if(Seconds > 59)
	{
		Minutes++;
		Seconds = 0;
	}
}

void ALevel1::StartBloobeSpawnTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, (TEXT("Bloobe Spawn")));
	SpawnEnemy(BloobeClass);
}

void ALevel1::StartBloobarSpawnTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, (TEXT("Bloobar Spawn")));
	SpawnEnemy(BloobarClass);
}

void ALevel1::StartBlooboxSpawnTimer()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Bloobox Spawn")));
	SpawnEnemy(BlooboxClass);
}

void ALevel1::SpawnEnemy(TSubclassOf<AEnemy> EnemyBP)
{
	if(EnemyBP) GetWorld()->SpawnActor<AEnemy>(EnemyBP, PlayerRef->GetActorLocation() + FVector(SpawnDistance, 0, 0), FRotator::ZeroRotator);
}
