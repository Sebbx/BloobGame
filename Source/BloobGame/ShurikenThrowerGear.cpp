// Fill out your copyright notice in the Description page of Project Settings.


#include "ShurikenThrowerGear.h"

#include "PlayerPawn.h"
#include "Shuriken.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UShurikenThrowerGear::UShurikenThrowerGear()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	
	// ...
}


// Called when the game starts
void UShurikenThrowerGear::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UShurikenThrowerGear::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

