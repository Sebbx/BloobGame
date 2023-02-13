// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelUpUI.h"

#include "ElectroFieldGear.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void ULevelUpUI::Initialize(APlayerPawn* PlayerPawn, UFloatingPawnMovement* FloatingPawnMovement, UHealthComponent* HealthComponent, UCannonWeaponGear* CannonWeaponGear, UShurikensGear* ShurikensGear, UElectroFieldGear* ElectroFieldGear)
{
	PlayerPawnRef = PlayerPawn;
	FloatingPawnMovementRef = FloatingPawnMovement;
	HealthComponentRef = HealthComponent;
	CannonWeaponGearRef = CannonWeaponGear;
	ShurikensGearRef = ShurikensGear;
	ElectroFieldGearRef = ElectroFieldGear;

	AvailableItems = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->EquipmentList;
	
	DrawUpgradeCategories();
	DrawItemsForPanels();
	
	SetPanelName(FText::AsCultureInvariant(Panel1Item), 1);
	SetPanelDescription(GetDescriptionOfItem(Panel1Item), 1);

	SetPanelName(FText::AsCultureInvariant(Panel2Item), 2);
	SetPanelDescription(GetDescriptionOfItem(Panel2Item), 2);

	SetPanelName(FText::AsCultureInvariant(Panel3Item), 3);
	SetPanelDescription(GetDescriptionOfItem(Panel3Item), 3);

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
	GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = true;

	ButtonPanel1->OnClicked.AddDynamic(this, &ULevelUpUI::Button1Clicked);
	ButtonPanel2->OnClicked.AddDynamic(this, &ULevelUpUI::Button2Clicked);
	ButtonPanel3->OnClicked.AddDynamic(this, &ULevelUpUI::Button3Clicked);
}

void ULevelUpUI::DrawUpgradeCategories()
{
	CannonWeaponGearRef->DrawTheUpgradeCategory();
	ShurikensGearRef->DrawTheUpgradeCategory();
	ElectroFieldGearRef->DrawTheUpgradeCategory();
}

void ULevelUpUI::DrawItemsForPanels()
{
	if(!AvailableItems.IsEmpty())
	{
		Panel1Item = AvailableItems[FMath::RandRange(0, AvailableItems.Num() - 1)];
		if(AvailableItems.Contains("ElectroField")) Panel1Item = "ElectroField"; // TESTING ONLY
		AvailableItems.Remove(Panel1Item);
	}

	if(!AvailableItems.IsEmpty())
	{
		Panel2Item = AvailableItems[FMath::RandRange(0, AvailableItems.Num() - 1)];
		AvailableItems.Remove(Panel2Item);
	}

	if(!AvailableItems.IsEmpty())
	{
		Panel3Item = AvailableItems[FMath::RandRange(0, AvailableItems.Num() - 1)];
	}
}

FText ULevelUpUI::GetDescriptionOfItem(FString Item)
{
	if (Item == "Cannon") return FText::AsCultureInvariant(CannonWeaponGearRef->GetDescription());
	//if (Item == "Health") return FText::AsCultureInvariant(HealthComponentRef->GetDescritpion(HealthUpgradeCategory));
	if (Item == "Shurikens") return FText::AsCultureInvariant(ShurikensGearRef->GetDescription());
	if (Item == "ElectroField") return FText::AsCultureInvariant(ElectroFieldGearRef->GetDescription());
	else return FText::AsCultureInvariant("");
}

void ULevelUpUI::UpgradeItem(FString Item)
{
	if (Item == "Cannon") CannonWeaponGearRef->Upgrade();
	if (Item == "Shurikens") ShurikensGearRef->Upgrade();
	if (Item == "ElectroField") ElectroFieldGearRef->Upgrade();
}

void ULevelUpUI::SetPanelName(FText PanelName, int PanelIndex)
{
	switch(PanelIndex)
	{
		case 1: if (NamePanel1) NamePanel1->SetText(PanelName); break;
		case 2: if (NamePanel2) NamePanel2->SetText(PanelName); break;
		case 3: if (NamePanel3) NamePanel3->SetText(PanelName); break;
		default: break;
	}
}

void ULevelUpUI::SetPanelDescription(FText PanelDescription, int PanelIndex)
{
	switch(PanelIndex)
	{
		case 1: if (DescriptionPanel1) DescriptionPanel1->SetText(PanelDescription); break;
		case 2: if (DescriptionPanel2) DescriptionPanel2->SetText(PanelDescription); break;
		case 3: if (DescriptionPanel3) DescriptionPanel3->SetText(PanelDescription); break;
		default: break;
	}
}

void ULevelUpUI::Button1Clicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Button1 Clicked")));

	if(Panel1Item != "")
	{
		UpgradeItem(Panel1Item);
		ClearLevelUpMenu();
	}	
}

void ULevelUpUI::Button2Clicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Button2 Clicked")));

	if(Panel2Item != "")
	{
		UpgradeItem(Panel2Item);
		ClearLevelUpMenu();
	}
}

void ULevelUpUI::Button3Clicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Button3 Clicked")));

	if(Panel3Item != "")
	{
		UpgradeItem(Panel3Item);
		ClearLevelUpMenu();
	}
}

void ULevelUpUI::ClearLevelUpMenu()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, StaticClass(), false);

	for (auto FoundWidget : FoundWidgets)
	{
		FoundWidget->RemoveFromParent();
	}

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
	GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = false;
}
