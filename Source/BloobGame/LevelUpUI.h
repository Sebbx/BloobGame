// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "CannonWeaponGear.h"
#include "HealthComponent.h"
#include "ShurikensGear.h"
#include "ElectroField.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpUI.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBGAME_API ULevelUpUI : public UUserWidget
{
	GENERATED_BODY()
	APlayerPawn* PlayerPawnRef;
	UFloatingPawnMovement* FloatingPawnMovementRef;
	UHealthComponent* HealthComponentRef;
	UCannonWeaponGear* CannonWeaponGearRef;
	UShurikensGear* ShurikensGearRef;
	UElectroFieldGear* ElectroFieldGearRef;

	FString Panel1Item;
	FString Panel2Item;
	FString Panel3Item;

	FString HealthUpgradeCategory;
	FString CannonUpgradeCategory;
	FString ShurikensUpgradeCategory;
	FString ElectroFieldUpgradeCategory;

public:
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* NamePanel1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* DescriptionPanel1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ButtonPanel1;

	
	UFUNCTION()
	void Button1Clicked();
	
	void Initialize(APlayerPawn* PlayerPawn, UFloatingPawnMovement* FloatingPawnMovement, UHealthComponent* HealthComponent, UCannonWeaponGear* CannonWeaponGear, UShurikensGear* ShurikensGear, UElectroFieldGear* ElectroFieldGear);
	void DrawItemsForPanels(TArray<FString> Items);
	void DrawUpgradeCategories();
	
	void SetPanelName(FText PanelName, int PanelIndex);
	void SetPanelDescription(FText PanelDescription, int PanelIndex);
};
