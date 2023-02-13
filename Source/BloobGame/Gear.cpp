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

bool UGear::CheckThatIsFullyUpgraded()
{
	if ((LevelCat1 >= DescriptionsCat1.Num()) && (LevelCat2 >= DescriptionsCat2.Num()) && (LevelCat3 >= DescriptionsCat3.Num()))
	{
		return true;
	}
	else return false;
}

void UGear::DrawTheUpgradeCategory()
{
	if(Categories.Num()>0) CurrentUpgradeCategory = Categories[FMath::RandRange(0, Categories.Num() - 1)];
}

FString UGear::GetDescription()
{
	if(IsUnlocked)
	{
		if (CurrentUpgradeCategory == "1st") return DescriptionsCat1[LevelCat1];
		if (CurrentUpgradeCategory == "2nd") return DescriptionsCat2[LevelCat2];
		if (CurrentUpgradeCategory == "3rd") return DescriptionsCat3[LevelCat3];
		else return "No expected case in GetDescription Gear.cpp";
	}
	else return UnlockDescription;
}

void UGear::RemoveItemFromEqList(FString ItemName)
{
	if(Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->EquipmentList.Contains(ItemName))
	{
		Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->EquipmentList.Remove(ItemName);
	}
	else UE_LOG(LogTemp, Error, TEXT("Gear.cpp | %s - Not found in EQ List"));
}

