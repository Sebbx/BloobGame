// Fill out your copyright notice in the Description page of Project Settings.


#include "ElectroField.h"
#include "Math/Vector.h"
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

	HandleAttack(DeltaTime);
	HandleScaling(DeltaTime);
}

void AElectroField::HandleAttack(float DeltaTime)
{
	TArray<AActor*> Arr;
	GetOverlappingActors(Arr, AEnemy::StaticClass());
	for(AActor* Enemy : Arr)
	{
		auto DamageTypeClass = UDamageType::StaticClass();
		UGameplayStatics::ApplyDamage(Enemy, Damage * DeltaTime, GetInstigatorController(), this, DamageTypeClass);
	}
}

void AElectroField::HandleScaling(float DeltaTime)
{
	if(CurrentScale < 0) Destroy();
	
	CurrentScale = FMath::Lerp(CurrentScale, TargetScale, ScalingUpRate);
	SetActorScale3D(FVector(CurrentScale, CurrentScale, 1));
	
	if(CurrentScale > TargetScale - TargetScale * .02 && !bScalingDown)
	{
		GetWorld()->GetTimerManager().SetTimer
			(
			TimerHandle,
			[&]() { TargetScale = -0.5;}, // lambda expression
			0.1f,
			true,
			1.0f
			);
		bScalingDown = true;
	}
}
