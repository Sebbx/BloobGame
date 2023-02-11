// Fill out your copyright notice in the Description page of Project Settings.


#include "Gear.h"

#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGear::UGear()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UGear::CheckThatisFullyUpgraded()
{
	if ((LevelCat1 >= DescriptionsCat1.Num() - 1) && (LevelCat2 >= DescriptionsCat2.Num() - 1) && (LevelCat3 >= DescriptionsCat3.Num() - 1))
	{
		IsFullyUpgraded = true;
		return true;
	}
	else IsFullyUpgraded = true; return false;
}

FString UGear::DrawTheUpgradeCategory()
{
	return Categories[FMath::RandRange(0, Categories.Num() - 1)];
}

FString UGear::GetDescritpion(FString Category)
{
	if(IsUnlocked)
	{
		if (Category == "1st") return DescriptionsCat1[LevelCat1];
		if (Category == "2nd") return DescriptionsCat2[LevelCat2];
		if (Category == "3rd") return DescriptionsCat3[LevelCat3];
		else return "No expected case in GetDescription Gear.cpp";
	}
	else return UnlockDescription;
}

void UGear::RemoveItemFromEqList(FString ItemName)
{
	Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->EquipmentList.Remove(ItemName);
}

