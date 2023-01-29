// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectroField.h"

#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AElectroField::AElectroField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	RootComponent = BaseMesh;
	
}

// Called when the game starts or when spawned
void AElectroField::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElectroField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<AActor*> Arr;
	GetOverlappingActors(Arr, AEnemy::StaticClass());

	for(AActor* Enemy : Arr)
	{
		AEnemy* Bloob = Cast<AEnemy>(Enemy);

		auto DamageTypeClass = UDamageType::StaticClass();
		UGameplayStatics::ApplyDamage(Enemy, 0.01, GetInstigatorController(), this, DamageTypeClass);
	}

}

