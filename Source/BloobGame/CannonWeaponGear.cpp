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
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Electro Field"));
	
}

void UCannonWeaponGear::BeginPlay()
{
	Super::BeginPlay();

	Penetration = 2;
	Damage = 2;
	
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
	if(ProjectileClass)
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
