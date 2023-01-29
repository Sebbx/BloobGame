// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectroFieldGear.h"

UElectroFieldGear::UElectroFieldGear()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UElectroFieldGear::BeginPlay()
{
	Super::BeginPlay();
}

void UElectroFieldGear::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UElectroFieldGear::GenerateElectroField()
{
	
}
