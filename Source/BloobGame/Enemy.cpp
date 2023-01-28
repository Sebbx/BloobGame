// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "AIController.h"
#include "AIHelpers.h"
#include "EnemyAIController.h"
#include "HealthComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Tasks/AITask.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	CapsuleComponent = GetCapsuleComponent();
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);
	
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
	auto DamageTypeClass = UDamageType::StaticClass();
	//TODO Attacking
	if (IsOverlappingActor(PlayerPawn) && CanAttack)
	{
		UGameplayStatics::ApplyDamage(PlayerPawn, Damage, GetOwner()->GetInstigatorController(), this, DamageTypeClass);
		CanAttack = false;

		GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemy::Reload, 1.f, false, ReloadTime);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::Reload()
{
	CanAttack = true;
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

