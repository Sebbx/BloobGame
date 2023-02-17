// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceCrystal.h"


// Sets default values
AExperienceCrystal::AExperienceCrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	RangeCollider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collider"));
}

// Called when the game starts or when spawned
void AExperienceCrystal::BeginPlay()
{
	RangeCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Super::BeginPlay();
}

