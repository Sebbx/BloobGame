// Fill out your copyright notice in the Description page of Project Settings.


#include "Level1.h"

#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"


ALevel1::ALevel1()
{
	PrimaryActorTick.bCanEverTick = true;
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
	PlayerRef->TimeDilation = &InitialTimeDilation;
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(LevelTimerHandle, this, &ALevel1::StartLevelTimer, LevelTimerRate, true, 1);
	GetWorld()->GetTimerManager().SetTimer(BloobeSpawnTimerHandle, this, &ALevel1::StartBloobeSpawnTimer, BloobeSpawnTimerRate, true, 0);

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), InitialTimeDilation);
}

void ALevel1::StartLevelTimer()
{
	Seconds++;
	if(Seconds > 59)
	{
		Minutes++;
		Seconds = 0;

		BloobeSpawnTimerRate *= BloobeSpawnRateMultiplayer;
		GetWorld()->GetTimerManager().ClearTimer(BloobeSpawnTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(BloobeSpawnTimerHandle, this, &ALevel1::StartBloobeSpawnTimer, BloobeSpawnTimerRate, true, BloobeSpawnTimerRate);

		if(Minutes >= BloobarMinuteActivation)
		{
			BloobarSpawnTimerRate *= BloobarSpawnRateMultiplayer;
			GetWorld()->GetTimerManager().ClearTimer(BloobarSpawnTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(BloobarSpawnTimerHandle, this, &ALevel1::StartBloobarSpawnTimer, BloobarSpawnTimerRate, true, 0);
		}
		if(Minutes >= BlooboxMinuteActivation)
		{
			BlooboxSpawnTimerRate *= BlooboxSpawnRateMultiplayer;
			GetWorld()->GetTimerManager().ClearTimer(BlooboxSpawnTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(BlooboxSpawnTimerHandle, this, &ALevel1::StartBlooboxSpawnTimer, BlooboxSpawnTimerRate, true, 0);
		}
	}
}

void ALevel1::StartBloobeSpawnTimer()
{
	SpawnEnemy(BloobeClass);
}

void ALevel1::StartBloobarSpawnTimer()
{
	SpawnEnemy(BloobarClass);
	UE_LOG(LogTemp, Warning, TEXT("Bloobar"));
}

void ALevel1::StartBlooboxSpawnTimer()
{
	SpawnEnemy(BlooboxClass);
	UE_LOG(LogTemp, Warning, TEXT("Bloobox"));
}

void ALevel1::SpawnEnemy(TSubclassOf<AEnemy> EnemyBP)
{
	auto SpawnLocation = FVector2d(FMath::VRand());
	SpawnLocation.Normalize();
	SpawnLocation *= SpawnDistance;
	if(EnemyBP) GetWorld()->SpawnActor<AEnemy>(EnemyBP, FVector(SpawnLocation.X, SpawnLocation.Y, 220) + PlayerRef->GetActorLocation(), FRotator::ZeroRotator);
}
