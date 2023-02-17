// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceSystem.h"

#include "PlayerPawn.h"

// Sets default values for this component's properties
UExperienceSystem::UExperienceSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UExperienceSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UExperienceSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UExperienceSystem::AddExp(float Exp)
{
	ExperiencePoints += Exp;
	if(ExperiencePoints >= ExpToNextLevel)
	{
		Cast<APlayerPawn>(GetOwner())->ShowLevelUpScreen();
		Cast<APlayerPawn>(GetOwner())->ExperienceLevel++;
		ExperiencePoints = 0;
		ExpToNextLevel += ExpToNextLevel * ExpGrowth;
	}
}

