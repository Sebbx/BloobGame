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

	DescriptionsCat1.Add("Radius +10%");
	DescriptionsCat1.Add("Radius +25%, Discharge rate -60%");
	DescriptionsCat1.Add("Radius +5%");

	DescriptionsCat2.Add("Duration of the Electro Field + 0.4s");
	DescriptionsCat2.Add("Duration of the Electro Field + 0.3s");
	DescriptionsCat2.Add("Duration of the Electro Field + 0.5s");

	DescriptionsCat3.Add("Damage + 5%");
	DescriptionsCat3.Add("Damage + 3%");
	DescriptionsCat3.Add("Damage + 7%, Discharge rate +5%");
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
					TargetScale += TargetScale * 0.1;
					LevelCat1++;
				} break;
				
			case 1:
				{
					TargetScale += TargetScale * 0.1;
					DischargeRate += DischargeRate * 0.6;
					LevelCat1++;
				} break;
				
			case 2:
				{
					TargetScale += TargetScale * 0.05;
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
					Duration += 0.4;
					LevelCat2++;
				} break;
				
			case 1:
				{
					Duration += 0.3;
					LevelCat2++;
				} break;
				
			case 2:
				{
					Duration += 0.5;
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
					Damage += Damage * 0.05;
					LevelCat3++;
				} break;
				
			case 1:
				{
					Damage += Damage * 0.03;
					LevelCat3++;
				} break;
				
			case 2:
				{
					Damage += Damage * 0.07;
					DischargeRate -= DischargeRate * 0.05;
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

