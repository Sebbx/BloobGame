// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBGAME_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ButtonPlay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ButtonExit;

	UFUNCTION()
	void Button1Clicked();

	UFUNCTION()
	void Button2Clicked();

	virtual void NativeConstruct() override;
	
};
