// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gear.h"
#include "ShurikensGear.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLOOBGAME_API UShurikensGear : public UGear
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Gear)
	TSubclassOf<class AShurikenProjectile> ProjectileClass;

public:	
	// Sets default values for this component's properties
	UShurikensGear();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	class USceneComponent* ShurikensPivot;

	UPROPERTY(EditAnywhere)
	int NumberOfShurikens = 1;
	
	UPROPERTY(EditAnywhere)
	float DistanceFromPivot = 300;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100;

	float Damage = 1;

	bool CanPivotRotate = false;

	void Upgrade();
private:

	TArray<AShurikenProjectile*> Projectiles;

	void DeployShurikens();
	void DestroyShurikens();

	void ConstructionForUpgrading();
		
};
