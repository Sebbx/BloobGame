// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gear.h"
#include "CannonWeaponGear.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBGAME_API UCannonWeaponGear : public UGear
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Gear)
	TSubclassOf<class AProjectile> ProjectileClass;

	FActorSpawnParameters ProjectileSpawnParameters;

public:	
	// Sets default values for this component's properties
	UCannonWeaponGear();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	UPROPERTY(EditAnywhere, Category = Gear)
	float ProjectileSpawnZOffset = -10;
	
	FTimerHandle TimerHandle;
	
	float FireRate = 1;
	FVector ProjectileSpawnLocation;
	FRotator ProjectileSpawnRotation = FRotator::ZeroRotator;
	
	void Shoot();
	void AimAtNearestEnemy();
	
	
};