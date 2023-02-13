// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Gear.h"
#include "ElectroFieldGear.generated.h"

UCLASS()
class BLOOBGAME_API UElectroFieldGear : public UGear
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Gear)
	TSubclassOf<class AElectroField> ElectroFieldClass; // TODO allocate this in player pawn to avoid this dumb fucking shit disappearing

public:	
	// Sets default values for this component's properties
	UElectroFieldGear();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Upgrade();

private:
	UPROPERTY(EditAnywhere, Category = Properties)
	float DischargeRate = 1;

	UPROPERTY(EditAnywhere, Category = Properties)
	float SpawnZOffset = 0;

	UPROPERTY(EditAnywhere, Category = Properties)
	float Damage = 0.2f;
	
	UPROPERTY(EditAnywhere, Category = Properties)
	float ScalingUpRate = 0.1;

	UPROPERTY(EditAnywhere, Category = Properties)
	float Duration = 2;

	UPROPERTY(EditAnywhere, Category = Properties)
	float TargetScale = 1;

	FTimerHandle TimerHandle;
	
	void GenerateElectroField();
	void StartEFieldGeneratorTimer();
	void ConstructionForUpgrading();
	
	
};

