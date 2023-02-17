// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExperienceCrystal.generated.h"

UCLASS()
class BLOOBGAME_API AExperienceCrystal : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* RangeCollider;
	
public:	
	// Sets default values for this actor's properties
	AExperienceCrystal();

	UPROPERTY(EditAnywhere)
	float Experience = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
