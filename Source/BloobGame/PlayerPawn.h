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
	class UInputAction* MoveAction;
	

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

private:
	UPROPERTY(EditAnywhere, Category = Utility)
	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, Category = Collision)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, Category = Meshes)
	class UStaticMeshComponent* BaseMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
