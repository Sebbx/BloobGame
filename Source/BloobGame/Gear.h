// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gear.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBGAME_API UGear : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGear();

protected:
	FString CurrentUpgradeCategory;

public:
	UPROPERTY(EditAnywhere, Category = GearClass)
	bool IsUnlocked;

	FString UnlockDescription;
	
	TArray<FString> DescriptionsCat1;
	TArray<FString> DescriptionsCat2;
	TArray<FString> DescriptionsCat3;

	UPROPERTY(EditAnywhere, Category = GearClass)
	int32 LevelCat1;

	UPROPERTY(EditAnywhere, Category = GearClass)
	int32 LevelCat2;

	UPROPERTY(EditAnywhere, Category = GearClass)
	int32 LevelCat3;


	UPROPERTY(EditAnywhere, Category = GearClass)
	bool IsFullyUpgraded;
	
	UPROPERTY(EditAnywhere, Category = GearClass)
	TArray<FString> Categories;


	bool CheckThatisFullyUpgraded();
	void DrawTheUpgradeCategory();
	FString GetDescritpion();
	void RemoveItemFromEqList(FString ItemName);
	
		
};
