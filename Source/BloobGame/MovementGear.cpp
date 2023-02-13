// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementGear.h"

#include "PlayerPawn.h"
#include "GameFramework/FloatingPawnMovement.h"

void UMovementGear::ConstructionForUpgrading()
{
	IsUnlocked = true;

	LevelCat1 = 0;
	LevelCat2 = 0;

	Categories.Add("1st");
	Categories.Add("2nd");

	DescriptionsCat1.Add("Movement speed +16%");
	DescriptionsCat1.Add("Movement speed +14%");
	DescriptionsCat1.Add("Movement speed +12");
	DescriptionsCat1.Add("Movement speed +10");
	DescriptionsCat1.Add("Movement speed +8");

	DescriptionsCat2.Add("Collecting range +25%");
	DescriptionsCat2.Add("Collecting range +15%");
	DescriptionsCat2.Add("Collecting range +7%");
}

void UMovementGear::Upgrade()
{
	if(CurrentUpgradeCategory == "1st")
	{
		APlayerPawn* PlayerRef = Cast<APlayerPawn>(GetOwner());
		float Speed = PlayerRef->GetMaxSpeed();
		switch(LevelCat1)
		{
		case 0:
			{
				PlayerRef->SetMaxSpeed(Speed + Speed * 0.16);
				LevelCat1++;
			} break;
		case 1:
			{
				PlayerRef->SetMaxSpeed(Speed + Speed * 0.14);
				LevelCat1++;
			} break;
		case 2:
			{
				PlayerRef->SetMaxSpeed(Speed + Speed * 0.12);
				LevelCat1++;
			} break;
		case 3:
			{
				PlayerRef->SetMaxSpeed(Speed + Speed * 0.10);
				LevelCat1++;
			} break;
		case 4:
			{
				PlayerRef->SetMaxSpeed(Speed + Speed * 0.08);
				LevelCat1++;
				Categories.Remove("1st");
			} break;
			default: break;
		} 
	}
	if(CurrentUpgradeCategory == "2nd")
	{
		float *CollectingRange = (&Cast<APlayerPawn>(GetOwner())->CollectingRange);
		switch(LevelCat2)
		{
		case 0:
			{
				*CollectingRange += *CollectingRange * 0.25;
				LevelCat2++;
			} break;
		case 1:
			{
				*CollectingRange += *CollectingRange * 0.15;
				LevelCat2++;
			} break;
		case 2:
			{
				*CollectingRange += *CollectingRange * 0.07;
				LevelCat2++;
				Categories.Remove("2nd");
			} break;
		default: break;
		}
	}
	if(CheckThatIsFullyUpgraded()) RemoveItemFromEqList("Movement");
}

void UMovementGear::BeginPlay()
{
	Super::BeginPlay();
	ConstructionForUpgrading();
}
