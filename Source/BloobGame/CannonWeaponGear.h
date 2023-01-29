// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CannonWeaponGear.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBGAME_API UCannonWeaponGear : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Gear)
	TSubclassOf<class AProjectile> ProjectileClass;

	FActorSpawnParameters ProjectileSpawnParameters;

	UPROPERTY(EditAnywhere, Category = Meshes)
	class UStaticMeshComponent* BaseMesh;

public:	
	// Sets default values for this component's properties
	UCannonWeaponGear();
	
	int Penetration;
	float Damage;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	UPROPERTY(EditAnywhere, Category = Debug)
	float AimYawCorrection = 5;
	
	UPROPERTY(EditAnywhere, Category = Features)
	float FireRate = 1;

	UPROPERTY(EditAnywhere, Category = Features)
	float AngleBetweenProjectiles = 5;

	UPROPERTY(EditAnywhere, Category = Features)
	int NumberOfProjectiles = 1;
	
	FTimerHandle TimerHandle;
	
	FVector ProjectileSpawnLocation;
	FRotator ProjectileSpawnRotationOffset = FRotator::ZeroRotator;
	FRotator LookAtEnemyRotation = FRotator::ZeroRotator;
	
	void Shoot();
	void AimAtNearestEnemy();
	
	
};