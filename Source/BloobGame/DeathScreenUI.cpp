// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathScreenUI.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UDeathScreenUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
	GetWorld()->GetFirstPlayerController()->bEnableMouseOverEvents = true;
	
	ButtonTryEgain->OnClicked.AddDynamic(this, &UDeathScreenUI::Button1Clicked);
	ButtonExit->OnClicked.AddDynamic(this, &UDeathScreenUI::Button2Clicked);
	
}

void UDeathScreenUI::Button1Clicked()
{
	FLatentActionInfo LatentInfo;
	UGameplayStatics::OpenLevel(GetWorld(), "Level1");
}

void UDeathScreenUI::Button2Clicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
