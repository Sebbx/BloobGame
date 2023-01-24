// Fill out your copyright notice in the Description page of Project Settings.


#include "CannonWeaponGear.h"

#include "Enemy.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

UCannonWeaponGear::UCannonWeaponGear()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCannonWeaponGear::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCannonWeaponGear::Shoot, FireRate, true, 0.f);
}

void UCannonWeaponGear::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCannonWeaponGear::Shoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, (TEXT("Shooting")));

	if(ProjectileClass)
	{
		GetWorld()->SpawnActor<AProjectile>(Cast<UClass>(ProjectileClass), GetOwner()->GetTransform());
	}
	
}
