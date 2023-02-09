// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShurikenProjectile.generated.h"

UCLASS()
class BLOOBGAME_API AShurikenProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Meshes)
	class UStaticMeshComponent* BaseMesh;
	
public:	
	// Sets default values for this actor's properties
	AShurikenProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 100;
	
	float Damage = 1;

	UFUNCTION()
	void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
};
