// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDUI.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPlayerHUDUI::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	if(ReferencesSet)
	{
		HealthPoints->SetText(FText::AsNumber(*HealthPointsRef));
		ShieldPoints->SetText(FText::AsNumber(*ShieldPoinsRef));
		ExperienceBar->SetPercent(*CurrentXPRef / *NextLevelXPRef);
		CurrentLevel->SetText(FText::AsNumber(*CurrentLevelRef));
	}
}

void UPlayerHUDUI::SetReferences(float* Health, float* Shield, float* CurrentXP, float* NextLevelXP, int *Level)
{
	HealthPointsRef = Health;
	ShieldPoinsRef = Shield;
	CurrentXPRef = CurrentXP;
	NextLevelXPRef = NextLevelXP;
	CurrentLevelRef = Level;
	ReferencesSet = true;
}
