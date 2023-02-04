// Fill out your copyright notice in the Description page of Project Settings.


#include "Shuriken.h"


// Sets default values
AShuriken::AShuriken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void AShuriken::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShuriken::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0, RotationSpeed  * DeltaTime, 0));

}

void AShuriken::DestroyShuriken()
{
	
}

