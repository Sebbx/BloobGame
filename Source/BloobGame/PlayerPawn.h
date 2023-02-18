// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "PlayerPawn.generated.h"

UCLASS()
class BLOOBGAME_API APlayerPawn : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IAMove;
	
	UPROPERTY(EditAnywhere, Category = Components)
	class UFloatingPawnMovement* FloatingPawnMovement;
	
	UPROPERTY(EditAnywhere, Category = Components)
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = Components)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = Components)
	class USceneComponent* ShurikensPivot;

	UPROPERTY(EditAnywhere, Category = Components)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, Category = Components)
	class UExperienceSystem* ExperienceSystem;
	
	UPROPERTY(EditAnywhere, Category = Meshes)
	class UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(EditAnywhere, Category = Meshes)
	class UStaticMeshComponent* ShieldMesh;

	UPROPERTY(EditAnywhere, Category = OnDamage)
	UMaterial* BaseMaterial;

	UPROPERTY(EditAnywhere, Category = OnDamage)
	UMaterial* OnDamageMaterial;

	UPROPERTY(EditAnywhere, Category = Gear)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, Category = Gear)
	class UCannonWeaponGear* Cannon;
	
	UPROPERTY(EditAnywhere, Category = Gear)
	class UElectroFieldGear* ElectroField;

	UPROPERTY(EditAnywhere, Category = Gear)
	class UMovementGear* MovementGear;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class ULevelUpUI> LevelUpUIClass;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class UDeathScreenUI> DeathScreenUIClass;
	
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<class UPlayerHUDUI> PlayerHUDUIClass;

	UPROPERTY()
	class ULevelUpUI* LevelUpUI;

	UPROPERTY()
	class UPlayerHUDUI* PlayerHudui;

	// DEBUG, DELETE LATER ************************

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IADebug1;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IADebug2;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IADebug3;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IADebug4;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IADebug5;

public:
	// Sets default values for this pawn's properties
	APlayerPawn();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float CollectingRange = 100;
	
	UPROPERTY(EditAnywhere, Category = Gear)
	class UShurikensGear* Shurikens;
	
	UPROPERTY(EditAnywhere, Category = GearClass)
	TArray<FString> EquipmentList;

	int ExperienceLevel = 1;

	int* MinutesRef;
	int* SecondsRef;

	float *TimeDilation;
	
	float GetMaxSpeed();
	void SetMaxSpeed(float NewMaxSpeed);
	void ShowLevelUpScreen();
	void ShowDeathScreen();
	void Die();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Debug1(const FInputActionValue& Value);
	void Debug2(const FInputActionValue& Value);
	void Debug3(const FInputActionValue& Value);
	void Debug4(const FInputActionValue& Value);
	void Debug5(const FInputActionValue& Value);

	
};
