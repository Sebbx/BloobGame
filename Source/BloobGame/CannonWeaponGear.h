// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Gear.h"
#include "CannonWeaponGear.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBGAME_API UCannonWeaponGear : public UGear
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Gear)
	TSubclassOf<class AProjectile> ProjectileClass;

public:	
	// Sets default values for this component's properties
	UCannonWeaponGear();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = Features)
	int Penetration = 1;
	
	UPROPERTY(EditAnywhere, Category = Features)
	float Damage = 1;
	
	UPROPERTY(EditAnywhere, Category = Features)
	float FireRate = 1;
	
	UPROPERTY(EditAnywhere, Category = Debug)
	float AimYawCorrection = 5;
	
	UPROPERTY(EditAnywhere, Category = Features)
	float AngleBetweenProjectiles = 5;

	UPROPERTY(EditAnywhere, Category = Features)
	int NumberOfProjectiles = 1;
private:
	
	FActorSpawnParameters ProjectileSpawnParameters;
	FTimerHandle TimerHandle;
	
	FVector ProjectileSpawnLocation;
	FRotator ProjectileSpawnRotationOffset = FRotator::ZeroRotator;
	FRotator LookAtEnemyRotation = FRotator::ZeroRotator;

	void ConstructionForUpgrading();
	void Shoot();
	void AimAtNearestEnemy();
};