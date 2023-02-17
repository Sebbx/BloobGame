// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceCrystal.h"

#include "PlayerPawn.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AExperienceCrystal::AExperienceCrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	RangeCollider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collider"));

	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void AExperienceCrystal::BeginPlay()
{
	RangeCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	float CollectingRange = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->CollectingRange;
	RangeCollider->SetWorldScale3D(FVector(CollectingRange, CollectingRange, 0.05));
	Super::BeginPlay();
}

