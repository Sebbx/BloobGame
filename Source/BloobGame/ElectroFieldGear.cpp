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
	if(IsUnlocked) GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UElectroFieldGear::GenerateElectroField, DeployRate, true, 1.f);
	
}

void UElectroFieldGear::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UElectroFieldGear::GenerateElectroField()
{
	if(ElectroFieldClass)
	{
		FVector SpawnLocation =  GetOwner()->GetActorLocation();
		SpawnLocation.Z += SpawnZOfsset;
		
		FTransform SpawnTransform {GetOwner()->GetActorRotation(), SpawnLocation, FVector(0.01, 0.01, 0.01)};
		
		AElectroField* ElectroFieldActor = GetWorld()->SpawnActorDeferred<AElectroField>(ElectroFieldClass, SpawnTransform);
		
		ElectroFieldActor->Damage = Damage;
		ElectroFieldActor->ScalingUpRate = ScalingUpRate;
		ElectroFieldActor->FullyScaledTime = FullyScaledTime;
		ElectroFieldActor->TargetScale = TargetScale;
		
		ElectroFieldActor->FinishSpawning(SpawnTransform);
	}
}
