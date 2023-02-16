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
	float* HealthPointsRef;
	float* ShieldPoinsRef;

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* HealthPoints;
		
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ShieldPoints;

	void SetReferences(float* HealthPoints, float* ShieldPoints);
};
