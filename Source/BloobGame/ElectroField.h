// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElectroField.generated.h"

UCLASS()
class BLOOBGAME_API AElectroField : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Mesh)
	class UStaticMeshComponent* BaseMesh;
	
public:	
	// Sets default values for this actor's properties
	AElectroField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
