// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gear.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBGAME_API UHealthComponent : public UGear
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UMaterial* BaseMaterial;
	UMaterial* OnDamageMaterial;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	UPROPERTY(EditAnywhere)
	float Health = 0.f;
	UPROPERTY(EditAnywhere)
	float HealthRegenMultiplier = 0;

	UPROPERTY(EditAnywhere)
	float MaxShield = 10;
	UPROPERTY(EditAnywhere)
	float Shield = 0;
	UPROPERTY(EditAnywhere)
	float ShieldRegenValue = 0.5;
	UPROPERTY(EditAnywhere)
	float ShieldRegenDelay = 2;

	UPROPERTY(EditAnywhere)
	bool HasShield = false;

	class UStaticMeshComponent* ShieldMeshRef;

	void Upgrade();

	// Shield
	void ActivateShield();
	void DeactivateShield();

private:
	UPROPERTY(EditAnywhere, Category = OnDamage)
	float TimeToDehighlight = 0.05;
	
	UPROPERTY(EditAnywhere, Category = Debug)
	bool LogHealth = false;

	FTimerHandle HighlightTimerHandle;
	FTimerHandle HealthRegenTimerHandle;
	FTimerHandle ShieldRegenTimerHandle;

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Insigator, AActor* DamageCauser);

	void DeHighlight();
	void Highlight();
	void ConstructionForUpgrading();
	void StartHealthRegenTimer();
	void RegenerateHealth();
	void StartShieldRegenTimer();
	void RegenerateShield();
};
