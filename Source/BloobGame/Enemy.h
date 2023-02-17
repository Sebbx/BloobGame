// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class BLOOBGAME_API AEnemy : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AEnemy();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = Meshes)
	class UStaticMeshComponent* BaseMesh;

	void Die();

private:
	class AAIController* AIController;
	
	UPROPERTY(EditAnywhere, Category = Components)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = OnDamage)
	UMaterial* BaseMaterial;

	UPROPERTY(EditAnywhere, Category = OnDamage)
	UMaterial* OnDamageMaterial;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AExperienceCrystal> ExpCrClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemy> BloobClassToSpawnAfterDeath;
	
	UPROPERTY(EditAnywhere)
	float AcceptableRadius;

	UPROPERTY(EditAnywhere)
	float Damage = 1;

	UPROPERTY(EditAnywhere)
	float ReloadTime = 2;

	UPROPERTY(EditAnywhere)
	float SpawnDistanceFromCenterAfterDeath = 30;

	UPROPERTY(EditAnywhere)
	int NumberOfBloobsToSpawnAfterDeath = 0;

	UPROPERTY(EditAnywhere)
	FString BloobType = "";
	
	class UCapsuleComponent* CapsuleComponent;
	APawn* PlayerPawn;
	FTimerHandle TimerHandle;
	bool CanAttack = true;
	
	void Reload();
	void HandleAttack();
};