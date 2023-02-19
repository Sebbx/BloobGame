// Fill out your copyright notice in the Description page of Project Settings.
#include "ElectroFieldGear.h"
#include "ElectroField.h"

UElectroFieldGear::UElectroFieldGear()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UElectroFieldGear::ConstructionForUpgrading()
{
	LevelCat1 = 0;
	LevelCat2 = 0;
	LevelCat3 = 0;

	UnlockDescription = "This gear generates electric fields that constantly damaging enemy Bloobs in range";
	Categories.Add("1st");
	Categories.Add("2nd");
	Categories.Add("3rd");

	DescriptionsCat1.Add("Radius +20%");
	DescriptionsCat1.Add("Radius +25%, Discharge rate -35%");
	DescriptionsCat1.Add("Radius +12%");

	DescriptionsCat2.Add("Duration of the Electro Field + 0.7s");
	DescriptionsCat2.Add("Duration of the Electro Field + 0.7s");
	DescriptionsCat2.Add("Duration of the Electro Field + 0.1s");

	DescriptionsCat3.Add("Damage + 15%");
	DescriptionsCat3.Add("Damage + 15%");
	DescriptionsCat3.Add("Damage + 15%, Discharge rate +20%");
}

void UElectroFieldGear::Upgrade()
{
	if(IsUnlocked)
	{
		if(CurrentUpgradeCategory == "1st")
		{
			switch(LevelCat1)
			{
			case 0:
				{
					TargetScale += TargetScale * 0.20;
					LevelCat1++;
				} break;
				
			case 1:
				{
					TargetScale += TargetScale * 0.25;
					DischargeRate += DischargeRate * 0.35;
					LevelCat1++;
				} break;
				
			case 2:
				{
					TargetScale += TargetScale * 0.12;
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
					Duration += 0.7;
					LevelCat2++;
				} break;
				
			case 1:
				{
					Duration += 0.7;
					LevelCat2++;
				} break;
				
			case 2:
				{
					Duration += 1;
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
					Damage += Damage * 0.15;
					LevelCat3++;
				} break;
				
			case 1:
				{
					Damage += Damage * 0.15;
					LevelCat3++;
				} break;
				
			case 2:
				{
					Damage += Damage * 0.15;
					DischargeRate -= DischargeRate * 0.2;
					LevelCat3++;
					Categories.Remove("3rd");
				} break;
			default: break;
			}
		}
	}
	else IsUnlocked = true;
	if(CheckThatIsFullyUpgraded()) RemoveItemFromEqList("ElectroField");
	StartEFieldGeneratorTimer();
}

void UElectroFieldGear::BeginPlay()
{
	Super::BeginPlay();
	ConstructionForUpgrading();
	if(IsUnlocked) StartEFieldGeneratorTimer();
}

void UElectroFieldGear::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UElectroFieldGear::GenerateElectroField()
{
	if(ElectroFieldClass)
	{
		FVector SpawnLocation =  GetOwner()->GetActorLocation();
		SpawnLocation.Z += SpawnZOffset;
		
		FTransform SpawnTransform {GetOwner()->GetActorRotation(), SpawnLocation, FVector(0.01, 0.01, 0.01)};
		
		AElectroField* ElectroFieldActor = GetWorld()->SpawnActorDeferred<AElectroField>(ElectroFieldClass, SpawnTransform);
		
		ElectroFieldActor->Damage = Damage;
		ElectroFieldActor->ScalingUpRate = ScalingUpRate;
		ElectroFieldActor->FullyScaledTime = Duration;
		ElectroFieldActor->TargetScale = TargetScale;
		
		ElectroFieldActor->FinishSpawning(SpawnTransform);
	}
}

void UElectroFieldGear::StartEFieldGeneratorTimer()
{
	if(TimerHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UElectroFieldGear::GenerateElectroField, DischargeRate, true, 1.f);
}

