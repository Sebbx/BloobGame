// Fill out your copyright notice in the Description page of Project Settings.


#include "ShurikenProjectile.h"

// Sets default values
AShurikenProjectile::AShurikenProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShurikenProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShurikenProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0, RotationSpeed * DeltaTime, 0));
}

