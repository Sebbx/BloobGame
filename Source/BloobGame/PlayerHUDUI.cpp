// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDUI.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UPlayerHUDUI::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	if(ReferencesSet && MinutesRef != nullptr && SecondsText != nullptr)
	{
		float a = 1;
		HealthPoints->SetText(FText::AsNumber(*HealthPointsRef));
		ShieldPoints->SetText(FText::AsNumber(*ShieldPoinsRef));
		ExperienceBar->SetPercent(*CurrentXPRef / *NextLevelXPRef);
		CurrentLevel->SetText(FText::AsNumber(*CurrentLevelRef));
		FString MinutesFText = FString::FromInt(*MinutesRef) + ":";
		MinutesText->SetText(FText::FromString(MinutesFText));
		SecondsText->SetText(FText::AsNumber(*SecondsRef));
	}

	if(*MinutesRef >= 15 && VictoryUIClass)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.01);
		auto VictoryUI = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), VictoryUIClass);
		VictoryUI->AddToPlayerScreen();
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

void UPlayerHUDUI::SetLevelTimerReferences(int* Minutes, int* Seconds)
{
	MinutesRef = Minutes;
	SecondsRef = Seconds;
}