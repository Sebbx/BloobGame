// Fill out your copyright notice in the Description page of Project Settings.
#include "ShurikensGear.h"
#include "ShurikenProjectile.h"

// Sets default values for this component's properties
UShurikensGear::UShurikensGear()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UShurikensGear::BeginPlay()
{
	Super::BeginPlay();
	
	if(ProjectileClass) DeployShurikens();
	
	// ...
}


// Called every frame
void UShurikensGear::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(ShurikensPivot)
	{
		ShurikensPivot->AddLocalRotation(FRotator(0, RotationSpeed * DeltaTime, 0));
	}
	// ...
}

void UShurikensGear::DeployShurikens()
{
	DestroyShurikens();
	
	float AngleBetweenEachShuriken = 0;
	if(NumberOfShurikens > 0) AngleBetweenEachShuriken = 360 / NumberOfShurikens;
	
	for (int i = 0; i < NumberOfShurikens; i++)
	{
		AShurikenProjectile* Projectile = GetWorld()->SpawnActor<AShurikenProjectile>(ProjectileClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if(ShurikensPivot) Projectile->GetRootComponent()->AttachToComponent(ShurikensPivot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Projectile->SetActorLocation(FVector(DistanceFromPivot, 0, 0));

		ShurikensPivot->AddLocalRotation(FRotator(0, AngleBetweenEachShuriken, 0));

		Projectiles.Add(Projectile);
	}
	
}

void UShurikensGear::DestroyShurikens()
{
	for (AShurikenProjectile* Projectile : Projectiles)
	{
		Projectile->Destroy();
	}
}

