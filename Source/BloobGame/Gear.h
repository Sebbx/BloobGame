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
	TArray<FString> Categories;
	FString UnlockDescription;

	int32 LevelCat1;
	int32 LevelCat2;
	int32 LevelCat3;

	bool IsUnlocked;
	bool IsFullyUpgraded;

public:
	TArray<FString> DescriptionsCat1;
	TArray<FString> DescriptionsCat2;
	TArray<FString> DescriptionsCat3;

	FString DrawTheUpgradeCategory();
		
};
