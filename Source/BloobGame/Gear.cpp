// Fill out your copyright notice in the Description page of Project Settings.


#include "Gear.h"

// Sets default values for this component's properties
UGear::UGear()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

FString UGear::DrawTheUpgradeCategory()
{
	if (!Categories.IsEmpty())
	{
		int RandomInt = FMath::RandRange(0, Categories.Num());
		UE_LOG(LogTemp, Error, TEXT("%i"), Categories.Num());
	}
	return "A";
}

