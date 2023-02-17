// Fill out your copyright notice in the Description page of Project Settings.
#include "HealthComponent.h"

#include "Enemy.h"
#include "PlayerPawn.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::ConstructionForUpgrading()
{
	IsUnlocked = true;
	
	LevelCat1 = 0;
	LevelCat2 = 0;
	LevelCat3 = 0;

	Categories.Add("1st");
	Categories.Add("2nd");
	Categories.Add("3rd");
	
	DescriptionsCat1.Add("Your Bloob will regenerate health at 1% Max HP per second");
	DescriptionsCat1.Add("Health regeneration +0.2% of Max HP per second");
	DescriptionsCat1.Add("Health regeneration +0.3% of Max HP per second");

	DescriptionsCat2.Add("Max HP +5");
	DescriptionsCat2.Add("Max HP +3");
	DescriptionsCat2.Add("Max HP +7");

	DescriptionsCat3.Add("Gain personal shield that blocks damage and regenerate over time");
	DescriptionsCat3.Add("Max SP + 5");
	DescriptionsCat3.Add("Regeneration of shield + 0.2 SP per second");
	DescriptionsCat3.Add("Max SP + 5, Regeneration of shield + 0.3 SP per second");
	DescriptionsCat3.Add("Regeneration delay of shield -1 second");
}

void UHealthComponent::Upgrade()
{
	if(CurrentUpgradeCategory == "1st")
	{
		switch(LevelCat1)
		{
		case 0:
			{
				HealthRegenMultiplier = 0.01;
				LevelCat1++;
			} break;
				
		case 1:
			{
				HealthRegenMultiplier += 0.002;
				LevelCat1++;
			} break;
				
		case 2:
			{
				HealthRegenMultiplier += 0.003;
				LevelCat1++;
				Categories.Remove("1st");
			} break;
		default: break;
		}
		StartHealthRegenTimer();
	}
	if(CurrentUpgradeCategory == "2nd")
	{
		switch(LevelCat2)
		{
		case 0:
			{
				MaxHealth += 5;
				Health += 5;
				if(Health > MaxHealth) Health = MaxHealth;
				LevelCat2++;
			} break;
				
		case 1:
			{
				MaxHealth += 3;
				Health += 3;
				if(Health > MaxHealth) Health = MaxHealth;
				LevelCat2++;
			} break;
				
		case 2:
			{
				MaxHealth += 7;
				Health += 7;
				if(Health > MaxHealth) Health = MaxHealth;
				LevelCat2++;
				Categories.Remove("2nd");
			} break;
		default: break;
		}
	}
	if(CurrentUpgradeCategory == "3rd")
	{
		switch(LevelCat3)
		{
		case 0:
			{
				HasShield = true;
				Shield = MaxShield;
				LevelCat3++;
			} break;

		case 1:
			{
				MaxShield += 5;
				LevelCat3++;
			} break;

		case 2:
			{
				ShieldRegenValue += 0.2;
				LevelCat3++;
			} break;

		case 3:
			{
				MaxShield += 5;
				ShieldRegenValue += 0.3;
				LevelCat3++;
			} break;

		case 4:
			{
				ShieldRegenDelay -= 1;
				LevelCat3++;
				Categories.Remove("3rd");
			} break;

			default: break;
		}
	}
	if(CheckThatIsFullyUpgraded()) RemoveItemFromEqList("Health");
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	ConstructionForUpgrading();

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(LogHealth) UE_LOG(LogTemp, Warning, TEXT("%f"), Health);

	if(ShieldMeshRef)
	{
		if(Shield > 0) ShieldMeshRef->SetVisibility(true);
		else ShieldMeshRef->SetVisibility(false);
	}

	if(Health <= 0)
	{
		if(GetOwner()->IsA(APlayerPawn::StaticClass())) Cast<APlayerPawn>(GetOwner())->Die();
		else Cast<AEnemy>(GetOwner())->Die();
	}
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Insigator, AActor* DamageCauser)
{
	if(Shield > 0)
	{
		Shield -= Damage;
		if(Shield < 0)
		{
			Health += Shield;
			Shield = 0;
		}
	}
	else
	{
		Health -= Damage;
	}
	Highlight();
	StartShieldRegenTimer();
}

void UHealthComponent::Highlight()
{
	GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, OnDamageMaterial);
	GetWorld()->GetTimerManager().SetTimer(HighlightTimerHandle, this, &UHealthComponent::DeHighlight, 1, false, TimeToDehighlight);
}

void UHealthComponent::DeHighlight()
{
	GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetMaterial(0, BaseMaterial);
}

void UHealthComponent::StartHealthRegenTimer()
{
	if(HealthRegenTimerHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(HealthRegenTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(HealthRegenTimerHandle, this, &UHealthComponent::RegenerateHealth, 1, true, 0);
}

void UHealthComponent::RegenerateHealth()
{
	if(Health<MaxHealth) Health += MaxHealth * HealthRegenMultiplier;
	if(Health>MaxHealth) Health = MaxHealth;
}

void UHealthComponent::StartShieldRegenTimer()
{
	if(HasShield)
	{
		if(ShieldRegenTimerHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(ShieldRegenTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(ShieldRegenTimerHandle, this, &UHealthComponent::RegenerateShield, 1, true, ShieldRegenDelay);
	}
}

void UHealthComponent::RegenerateShield()
{
	if(Shield<MaxShield) Shield += ShieldRegenValue;
	if(Shield>MaxShield) Shield = MaxShield;
}

void UHealthComponent::ActivateShield()
{
	ShieldMeshRef->SetVisibility(true);
}

void UHealthComponent::DeactivateShield()
{
	ShieldMeshRef->SetVisibility(false);
}



