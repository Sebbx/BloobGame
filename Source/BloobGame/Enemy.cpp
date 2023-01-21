// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "AIController.h"
#include "AIHelpers.h"
#include "EnemyAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Tasks/AITask.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AAIController* AIController = Cast<AAIController>(GetController());
	AIController->MoveToLocation(PlayerPawn->GetActorLocation(), AcceptableRadius);
	
	HandleAttack();

}

void AEnemy::HandleAttack()
{
	//TODO Attacking
	if (IsOverlappingActor(PlayerPawn))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Yellow, (TEXT("Overlapping")));
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

