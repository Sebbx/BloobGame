// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy.h"
#include "AIController.h"
#include "ExperienceCrystal.h"
#include "HealthComponent.h"
#include "PlayerPawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

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

	SpawnDefaultController();
	AIController = Cast<AAIController>(GetController());
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if(HealthComponent)
	{
		HealthComponent->Health = HealthComponent->MaxHealth;
		
		if (BaseMaterial && OnDamageMaterial)
		{
			HealthComponent->BaseMaterial = BaseMaterial;
			HealthComponent->OnDamageMaterial = OnDamageMaterial;
		}
		else UE_LOG(LogTemp, Error, TEXT("AEnemy: One or both Materials for HealthComponent is not set"));
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerPawn)
	{
		MoveToLocation = PlayerPawn->GetActorLocation();
	}
	
	if(AIController) AIController->MoveToLocation(MoveToLocation, AcceptableRadius, false);
	
	HandleAttack();
}

void AEnemy::HandleAttack()
{
	const auto DamageTypeClass = UDamageType::StaticClass();
	
	if (IsOverlappingActor(PlayerPawn) && CanAttack)
	{
		UGameplayStatics::ApplyDamage(PlayerPawn, Damage, GetOwner()->GetInstigatorController(), this, DamageTypeClass);
		CanAttack = false;

		GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemy::Reload, 1.f, false, ReloadTime);
	}
}

void AEnemy::Reload()
{
	CanAttack = true;
	GetWorldTimerManager().ClearTimer(TimerHandle);
}

void AEnemy::Die()
{
	AIController->StopMovement();
	
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FVector ExpSpawnLoc = GetActorLocation();
	ExpSpawnLoc.Z = 95;
	if (ExpCrClass) GetWorld()->SpawnActor<AExperienceCrystal>(ExpCrClass, ExpSpawnLoc, FRotator::ZeroRotator);
	
	if (NumberOfBloobsToSpawnAfterDeath > 0 && BloobClassToSpawnAfterDeath)
	{
		TArray<AEnemy*> SpawnedBloobs;
		float OffsetAngle = 360 / NumberOfBloobsToSpawnAfterDeath;
		for (int i = 0; i < NumberOfBloobsToSpawnAfterDeath; i++)
		{
			AEnemy *SpawnedBloob = GetWorld()->SpawnActor<AEnemy>(BloobClassToSpawnAfterDeath, GetActorLocation(), FRotator::ZeroRotator);
			if(SpawnedBloob)
			{
				SpawnedBloobs.Add(SpawnedBloob);
				SpawnedBloob->AddActorWorldRotation(FRotator(0, OffsetAngle * i, 0));
				SpawnedBloob->AddActorLocalOffset(FVector(SpawnDistanceFromCenterAfterDeath, 0, 0));
				SpawnedBloob->SetActorEnableCollision(false);
			}
		}
		for (auto SpawnedBloob : SpawnedBloobs)
		{
			SpawnedBloob->SetActorEnableCollision(true);
		}
	}
	AIController->StopMovement();
	Destroy();
}
