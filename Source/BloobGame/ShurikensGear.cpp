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

void UShurikensGear::ConstructionForUpgrading()
{
	IsUnlocked = false;
	IsFullyUpgraded = false;

	LevelCat1 = 0;
	LevelCat2 = 0;
	LevelCat3 = 0;

	UnlockDescription = "Sharp Shuriken that orbit around you and deals 1 damage while coming through enemy";
	Categories.Add("1st");
	Categories.Add("2nd");
	Categories.Add("3rd");
	
	DescriptionsCat1.Add("Shuriken +1");
	DescriptionsCat1.Add("Shuriken +1");
	DescriptionsCat1.Add("Shuriken +1, Orbiting speed -20%");

	DescriptionsCat2.Add("Damage +0.5");
	DescriptionsCat2.Add("Damage +0.5");

	DescriptionsCat3.Add("Orbiting speed +15%");
	DescriptionsCat3.Add("Orbiting speed +10%");
	DescriptionsCat3.Add("Orbiting speed +25%");
}

void UShurikensGear::Upgrade()
{
	if(IsUnlocked)
	{
		if(CurrentUpgradeCategory == "1st")
		{
			switch(LevelCat1)
			{
			case 0:
				{
					NumberOfShurikens++;
					LevelCat1++;
				} break;
			case 1:
				{
					NumberOfShurikens++;
					LevelCat1++;
				} break;
			case 2:
				{
					NumberOfShurikens++;
					RotationSpeed -= RotationSpeed * 0.2;
					LevelCat1++;
					Categories.Remove("1st");
				} break;
				default: break;
			}
		}
		if(CurrentUpgradeCategory == "2nd")
		{
			switch(LevelCat2)
			{
			case 0:
				{
					Damage += 0.5;
					LevelCat2++;
				} break;
			case 1:
				{
					Damage += 0.5;
					LevelCat2++;
					Categories.Remove("2nd");
				} break;
			default: break;
			}
		}
		if(CurrentUpgradeCategory == "3rd")
		{
			switch(LevelCat3)
			{
			case 0:
				{
					RotationSpeed += RotationSpeed * 0.15;
					LevelCat3++;
				} break;
			case 1:
				{
					RotationSpeed += RotationSpeed * 0.10;
					LevelCat3++;
				} break;
			case 2:
				{
					RotationSpeed += RotationSpeed * 0.25;
					LevelCat3++;
					Categories.Remove("3rd");
				} break;
			default: break;
			}
		}
	}
	else IsUnlocked = true;
	if(CheckThatisFullyUpgraded()) RemoveItemFromEqList("Shurikens");
	DeployShurikens();
}


// Called when the game starts
void UShurikensGear::BeginPlay()
{
	Super::BeginPlay();
	
	if(ProjectileClass && IsUnlocked) DeployShurikens();

	ConstructionForUpgrading();
	
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
		if(ShurikensPivot && Projectile)
		{
			Projectile->GetRootComponent()->AttachToComponent(ShurikensPivot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Projectile->AddActorWorldOffset(FVector(DistanceFromPivot, 0, 0));
			
			ShurikensPivot->AddLocalRotation(FRotator(0, AngleBetweenEachShuriken, 0));

			Projectiles.Add(Projectile);
		}
	}
	
}

void UShurikensGear::DestroyShurikens()
{
	if (!Projectiles.IsEmpty())
	{
		for (AShurikenProjectile* Projectile : Projectiles)
		{
			Projectile->Destroy();
		}
	}

}

