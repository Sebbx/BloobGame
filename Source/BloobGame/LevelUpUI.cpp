// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelUpUI.h"
#include "Components/TextBlock.h"

void ULevelUpUI::Initialize(APlayerPawn* PlayerPawn, UFloatingPawnMovement* FloatingPawnMovement, UHealthComponent* HealthComponent, UCannonWeaponGear* CannonWeaponGear, UShurikensGear* ShurikensGear, UElectroFieldGear* ElectroFieldGear)
{
	PlayerPawnRef = PlayerPawn;
	FloatingPawnMovementRef = FloatingPawnMovement;
	HealthComponentRef = HealthComponent;
	CannonWeaponGearRef = CannonWeaponGear;
	ShurikensGearRef = ShurikensGear;
	ElectroFieldGearRef = ElectroFieldGear;

	TArray<FString> Items;
	Items.Add("Movement");
	Items.Add("Health");
	Items.Add("Cannon");
	Items.Add("Shurikens");
	Items.Add("ElectroField");
	
	DrawUpgradeCategories();
	DrawItemsForPanels(Items);
}

void ULevelUpUI::DrawUpgradeCategories()
{
	//CannonWeaponGearRef->DrawTheUpgradeCategory();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CannonWeaponGearRef->DrawTheUpgradeCategory())
}

void ULevelUpUI::DrawItemsForPanels(TArray<FString> Items)
{
	Panel1Item = Items[FMath::RandRange(0, Items.Num() - 1)];
	Items.Remove(Panel1Item);
	Panel2Item = Items[FMath::RandRange(0, Items.Num() - 1)];
	Items.Remove(Panel2Item);
	Panel3Item = Items[FMath::RandRange(0, Items.Num() - 1)];
}

void ULevelUpUI::SetPanelName(FText PanelName, int PanelIndex)
{
	switch(PanelIndex)
	{
		case 1: if (NamePanel1) NamePanel1->SetText(PanelName); break;
		default: break;
	}
}

void ULevelUpUI::SetPanelDescription(FText PanelDescription, int PanelIndex)
{
	switch(PanelIndex)
	{
		case 1: if (DescriptionPanel1) DescriptionPanel1->SetText(PanelDescription); break;
		default: break;
	}
}


void ULevelUpUI::Button1Clicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Button1 Clicked")));
}
