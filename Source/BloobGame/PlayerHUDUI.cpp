// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDUI.h"

#include "Components/TextBlock.h"

void UPlayerHUDUI::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	if(ReferencesSet)
	{
		HealthPoints->SetText(FText::AsNumber(*HealthPointsRef));
		ShieldPoints->SetText(FText::AsNumber(*ShieldPoinsRef));
	}
}

void UPlayerHUDUI::SetReferences(float* Health, float* Shield)
{
	HealthPointsRef = Health;
	ShieldPoinsRef = Shield;
	ReferencesSet = true;
}
