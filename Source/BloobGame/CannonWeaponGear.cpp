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
}

void UCannonWeaponGear::ConstructionForUpgrading()
{
	LevelCat1 = 0;
	LevelCat2 = 0;
	LevelCat3 = 0;

	UnlockDescription = "Powerful Cannon that shoot big projectile every 1 second straight into nearest enemy";
	Categories.Add("1st");
	Categories.Add("2nd");
	Categories.Add("3rd");
	
	DescriptionsCat1.Add("Penetration +1, Firerate -15%");
	DescriptionsCat1.Add("Penetration +1, Firerate -15%");
	DescriptionsCat1.Add("Penetration +1, Firerate -15%");

	DescriptionsCat2.Add("Bullet +1, Firerate -25%, Spread +20%");
	DescriptionsCat2.Add("Bullet +1, Firerate -25%, Spread +17%");
	DescriptionsCat2.Add("Bullet +1, Firerate -20%, Spread +15%");

	DescriptionsCat3.Add("Firerate +30%");
	DescriptionsCat3.Add("Firerate +25%");
	DescriptionsCat3.Add("Firerate +15%, Spread -35%");
	
}

void UCannonWeaponGear::Upgrade()
{
	if(IsUnlocked)
	{
		if(CurrentUpgradeCategory == "1st")
		{
			switch(LevelCat1)
			{
			case 0:
				{
					FireRate += FireRate * 0.15;
					Penetration++;
					LevelCat1++;
				} break;
				
			case 1:
				{	
					Penetration++;
					FireRate += FireRate * 0.15;
					LevelCat1++;
				} break;
				
			case 2:
				{	
					Penetration++;
					AngleBetweenProjectiles += AngleBetweenProjectiles * 0.1;
					FireRate += FireRate * 0.15;
					LevelCat1++;
					Categories.Remove("1st");
				} break;
			default: break;
			}
		}
		if(CurrentUpgradeCategory == "2nd")
		{
			switch (LevelCat2)
			{
			case 0:
				{
					NumberOfProjectiles++;
					FireRate += FireRate * 0.25;
					AngleBetweenProjectiles += AngleBetweenProjectiles * 0.2;
					LevelCat2++;
				} break;
			case 1:
				{
					NumberOfProjectiles++;
					AngleBetweenProjectiles += AngleBetweenProjectiles * 0.17;
					FireRate += FireRate * 0.25;
					LevelCat2++;
				} break;
			case 2:
				{
					NumberOfProjectiles++;
					FireRate += FireRate * 0.20;
					AngleBetweenProjectiles += AngleBetweenProjectiles * 0.15;
					LevelCat2++;
					Categories.Remove("2nd");
				} break;
			default: break;
			}
		}
		if(CurrentUpgradeCategory == "3rd")
		{
			switch (LevelCat3)
			{
			case 0:
				{
					FireRate -= FireRate * 0.3;
					LevelCat3++;
				} break;
			case 1:
				{
					FireRate -= FireRate * 0.25;
					LevelCat3++;
				} break;
			case 2:
				{
					FireRate -= FireRate * 0.15;
					AngleBetweenProjectiles -= AngleBetweenProjectiles * 0.35;
					LevelCat3++;
					Categories.Remove("3rd");
				} break;
			default: break;
			}
		}
		StartShootingTimer();
	}
	else IsUnlocked = true;
	if(CheckThatIsFullyUpgraded()) RemoveItemFromEqList("Cannon");
}
void UCannonWeaponGear::BeginPlay()
{
	Super::BeginPlay();
	ConstructionForUpgrading();
	
	// This timer is managing shooting projectiles
	StartShootingTimer();
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
			LookAtEnemyRotation.Pitch = 0;
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

void UCannonWeaponGear::StartShootingTimer()
{
	if(TimerHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCannonWeaponGear::Shoot, FireRate, true, 0.f);
}

