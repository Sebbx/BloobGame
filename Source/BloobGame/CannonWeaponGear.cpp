// Fill out your copyright notice in the Description page of Project Settings.
#include "CannonWeaponGear.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Actor.h"

UCannonWeaponGear::UCannonWeaponGear()
{
	PrimaryComponentTick.bCanEverTick = true;
	ConstructionForUpgrading();
}

void UCannonWeaponGear::ConstructionForUpgrading()
{
	LevelCat1 = 0;
	LevelCat2 = 0;
	LevelCat3 = 0;
	IsUnlocked = false;
	IsFullyUpgraded = false;

	UnlockDescription = "Powerful Cannon that shoot big projectile every 1 second straight into nearest enemy";
	Categories.Add("1st");
	Categories.Add("2nd");
	Categories.Add("3rd");
	
	DescriptionsCat1.Add("Penetration +1");
	DescriptionsCat1.Add("Penetration +1, Firerate -5%");
	DescriptionsCat1.Add("Penetration +1, Spread +10%");

	DescriptionsCat2.Add("Bullet +1");
	DescriptionsCat2.Add("Bullet +1, Spread +10%");
	DescriptionsCat2.Add("Bullet +1, Firerate -5%");

	DescriptionsCat3.Add("Firerate +10%");
	DescriptionsCat3.Add("Firerate +15%");
	DescriptionsCat3.Add("Firerate +15%, Spread -25%");
}

void UCannonWeaponGear::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%i"), Categories.Num());
	
	// This timer is managing shooting projectiles
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCannonWeaponGear::Shoot, FireRate, true, 0.f);
}

void UCannonWeaponGear::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	ProjectileSpawnLocation = GetOwner()->GetActorLocation();
	
	AimAtNearestEnemy();
}

void UCannonWeaponGear::Shoot()
{
	//TODO EnemyInRange condition
	if(ProjectileClass && IsUnlocked)
	{
		for (int i = 0; i < NumberOfProjectiles; i++)
		{
			ProjectileSpawnRotationOffset.Yaw = (AngleBetweenProjectiles * i) - (AngleBetweenProjectiles * NumberOfProjectiles / 2) + AimYawCorrection;
			GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnLocation, LookAtEnemyRotation + ProjectileSpawnRotationOffset);
		}
	}
}

void UCannonWeaponGear::AimAtNearestEnemy()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), OutActors);

	if(!OutActors.IsEmpty())
	{
		float Distance;
		LookAtEnemyRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileSpawnLocation,
			UGameplayStatics::FindNearestActor(ProjectileSpawnLocation, OutActors, Distance)->GetActorLocation());
	}
}
