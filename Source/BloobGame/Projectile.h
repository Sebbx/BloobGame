// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BLOOBGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = Meshes)
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = Features)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	class UCannonWeaponGear* WeaponGear;
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle TimerHandle;
	int Penetration = 1;
	float Damage = 1;
	float TimeToDestroy = 2;

	UFUNCTION()
	void OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	void DestroyProjectile();
};
