// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gear.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBGAME_API UHealthComponent : public UGear
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = OnDamage)
	UMaterial* BaseMaterial;

	UPROPERTY(EditAnywhere, Category = OnDamage)
	UMaterial* OnDamageMaterial;

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	float Health = 0.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = OnDamage)
	float TimeToDehighlight = 0.05;

	FTimerHandle InputTimerHandle;

	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Insigator, AActor* DamageCauser);

	void DeHighlight();
	void Highlight();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
