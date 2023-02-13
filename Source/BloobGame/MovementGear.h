// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gear.h"
#include "MovementGear.generated.h"

/**
 * 
 */
UCLASS()
class BLOOBGAME_API UMovementGear : public UGear
{
	GENERATED_BODY()
	class UFloatingPawnMovement* FloatingPawnMovementRef;

	void ConstructionForUpgrading();

protected:
	virtual void BeginPlay() override;

public:
	void Upgrade();
	
};
