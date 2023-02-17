// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDUI.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBGAME_API UPlayerHUDUI : public UUserWidget
{
	GENERATED_BODY()

	bool ReferencesSet = false;
	int* CurrentLevelRef; 
	float* HealthPointsRef;
	float* ShieldPoinsRef;
	float* CurrentXPRef;
	float* NextLevelXPRef;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* HealthPoints;
		
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ShieldPoints;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CurrentLevel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* ExperienceBar;

	void SetReferences(float *HealthPoints, float *ShieldPoints, float *CurrentXP, float *NextLevelXP, int *Level);
};
