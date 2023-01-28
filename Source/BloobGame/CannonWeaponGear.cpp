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

void UCannonWeaponGear::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCannonWeaponGear::Shoot, FireRate, true, 0.f);
	
	Penetration = 2;
	Damage = 2;
}

void UCannonWeaponGear::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ProjectileSpawnLocation = GetOwner()->GetActorLocation();
	AimAtNearestEnemy();
}

void UCannonWeaponGear::Shoot()
{
	if(ProjectileClass)
	{
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation);
	}

	
}

void UCannonWeaponGear::AimAtNearestEnemy()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), OutActors);

	if(!OutActors.IsEmpty())
	{
		float Distance;
		ProjectileSpawnRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileSpawnLocation,
			UGameplayStatics::FindNearestActor(ProjectileSpawnLocation, OutActors, Distance)->GetActorLocation());
	}
}
