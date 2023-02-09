// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpUI.h"

#include "Components/TextBlock.h"

void ULevelUpUI::SetPanelName(FText PanelName)
{
	if (Name1stPanel)
	{
		Name1stPanel->SetText(PanelName);
	}
}

void ULevelUpUI::SetPanelDescription(FText PanelDescription)
{
	if (Description1stPanel)
	{
		Description1stPanel->SetText(PanelDescription);
	}
}
