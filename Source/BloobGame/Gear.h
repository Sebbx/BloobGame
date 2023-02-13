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
	bool IsUnlocked = false;

	UPROPERTY(VisibleAnywhere, Category = GearClass)
	FString UnlockDescription;
	
	UPROPERTY(VisibleAnywhere, Category = GearClass)
	TArray<FString> DescriptionsCat1;
	
	UPROPERTY(VisibleAnywhere, Category = GearClass)
	TArray<FString> DescriptionsCat2;
	
	UPROPERTY(VisibleAnywhere, Category = GearClass)
	TArray<FString> DescriptionsCat3;

	UPROPERTY(EditAnywhere, Category = GearClass)
	int32 LevelCat1;

	UPROPERTY(EditAnywhere, Category = GearClass)
	int32 LevelCat2;

	UPROPERTY(EditAnywhere, Category = GearClass)
	int32 LevelCat3;
	
	UPROPERTY(EditAnywhere, Category = GearClass)
	TArray<FString> Categories;

	FString GetDescription();
	bool CheckThatIsFullyUpgraded();
	void DrawTheUpgradeCategory();
	void RemoveItemFromEqList(FString ItemName);
	
		
};
