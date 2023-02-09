// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpUI.h"

#include "Components/TextBlock.h"

void ULevelUpUI::SetPanelName(FText PanelName, int PanelIndex)
{
	switch(PanelIndex)
	{
		case 1: if (NamePanel1) NamePanel1->SetText(PanelName); break;
		default: break;
	}
}

void ULevelUpUI::SetPanelDescription(FText PanelDescription, int PanelIndex)
{
	switch(PanelIndex)
	{
		case 1: if (DescriptionPanel1) DescriptionPanel1->SetText(PanelDescription); break;
		default: break;
	}
}
