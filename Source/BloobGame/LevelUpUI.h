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
	void SetPanelName(FText PanelName);

	void SetPanelDescription(FText PanelDescription);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Name1stPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Description1stPanel;
	
};
