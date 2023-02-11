// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelUpUI.h"

#include "ElectroFieldGear.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
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
}

void ULevelUpUI::DrawUpgradeCategories()
{
	CannonUpgradeCategory = CannonWeaponGearRef->DrawTheUpgradeCategory();
}

void ULevelUpUI::DrawItemsForPanels()
{
	Panel1Item = AvailableItems[FMath::RandRange(0, AvailableItems.Num() - 1)];
	AvailableItems.Remove(Panel1Item);
	Panel2Item = AvailableItems[FMath::RandRange(0, AvailableItems.Num() - 1)];
	AvailableItems.Remove(Panel2Item);
	Panel3Item = AvailableItems[FMath::RandRange(0, AvailableItems.Num() - 1)];
	Panel1Item = "Cannon";
}

FText ULevelUpUI::GetDescriptionOfItem(FString Item)
{
	if (Item == "Cannon") return FText::AsCultureInvariant(CannonWeaponGearRef->GetDescritpion(CannonUpgradeCategory));
	//if (Item == "Health") return FText::AsCultureInvariant(HealthComponentRef->GetDescritpion(HealthUpgradeCategory));
	//if (Item == "Shurikens") return FText::AsCultureInvariant(ShurikensGearRef->GetDescritpion(ShurikensUpgradeCategory));
	//if (Item == "ElectroField") return FText::AsCultureInvariant(ElectroFieldGearRef->GetDescritpion(ElectroFieldUpgradeCategory));
	else return FText::AsCultureInvariant("");
}

void ULevelUpUI::UpgradeItem(FString Item)
{
	if (Item == "Cannon") CannonWeaponGearRef->Upgrade(CannonUpgradeCategory);
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
	UpgradeItem(Panel1Item);
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
