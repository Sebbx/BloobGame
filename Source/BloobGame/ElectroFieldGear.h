// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "ElectroFieldGear.generated.h"

UCLASS()
class BLOOBGAME_API UElectroFieldGear : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Gear)
	TSubclassOf<class AElectroField> ElectroFieldClass;

public:	
	// Sets default values for this component's properties
	UElectroFieldGear();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category = Properties)
	float DeployRate = 1;

	UPROPERTY(EditAnywhere, Category = Properties)
	float SpawnZOfsset = 0;

	UPROPERTY(EditAnywhere, Category = Properties)
	float Damage = 0.2f;
	
	UPROPERTY(EditAnywhere, Category = Properties)
	float ScalingUpRate = 0.1;

	UPROPERTY(EditAnywhere, Category = Properties)
	float FullyScaledTime = 2;

	UPROPERTY(EditAnywhere, Category = Properties)
	float TargetScale = 1;

	UPROPERTY(EditAnywhere, Category = Properties)
	bool IsUnlocked = false;

	FTimerHandle TimerHandle;
	
	void GenerateElectroField();
	
	
};
