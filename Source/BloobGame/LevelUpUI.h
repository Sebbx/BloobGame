// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpUI.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBGAME_API ULevelUpUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPanelName(FText PanelName, int PanelIndex);

	void SetPanelDescription(FText PanelDescription, int PanelIndex);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* NamePanel1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* DescriptionPanel1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ButtonPanel1;
	
};
