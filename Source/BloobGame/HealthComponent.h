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

	float MaxHealth = 100.f;
	float Health = 0.f;

private:
	UPROPERTY(EditAnywhere, Category = OnDamage)
	float TimeToDehighlight = 0.05;
	
	UPROPERTY(EditAnywhere, Category = Debug)
	bool LogHealth = false;

	FTimerHandle InputTimerHandle;

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Insigator, AActor* DamageCauser);

	void DeHighlight();
	void Highlight();
};
