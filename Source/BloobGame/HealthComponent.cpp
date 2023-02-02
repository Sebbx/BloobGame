// Fill out your copyright notice in the Description page of Project Settings.
#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(Health <=0) GetOwner()->Destroy();
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Insigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;
	Health -= Damage;
	
	//Highlight actor when damage is taken
	Highlight();
}

void UHealthComponent::Highlight()
{
	GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, OnDamageMaterial);
	GetWorld()->GetTimerManager().SetTimer(InputTimerHandle, this, &UHealthComponent::DeHighlight, 1, false, TimeToDehighlight);
}

void UHealthComponent::DeHighlight()
{
	GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, BaseMaterial);
}



