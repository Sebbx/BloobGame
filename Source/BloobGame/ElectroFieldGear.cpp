// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectroFieldGear.h"

#include "ElectroField.h"

UElectroFieldGear::UElectroFieldGear()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UElectroFieldGear::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UElectroFieldGear::GenerateElectroField, FireRate, true, 0.f);
}

void UElectroFieldGear::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UElectroFieldGear::GenerateElectroField()
{
	if(ElectroFieldClass)
	{
		GetWorld()->SpawnActor<AElectroField>(ElectroFieldClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	}
}
