// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUI.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuUI::NativeConstruct()
{
	Super::NativeConstruct();
		
	ButtonPlay->OnClicked.AddDynamic(this, &UMainMenuUI::Button1Clicked);
	ButtonExit->OnClicked.AddDynamic(this, &UMainMenuUI::Button2Clicked);
	
}

void UMainMenuUI::Button1Clicked()
{
	FLatentActionInfo LatentInfo;
	UGameplayStatics::OpenLevel(GetWorld(), "Level1");
}

void UMainMenuUI::Button2Clicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

