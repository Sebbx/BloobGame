// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy.h"
#include "AIController.h"
#include "HealthComponent.h"
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
	
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if(HealthComponent)
	{
		HealthComponent->MaxHealth = MaxHealth;
		HealthComponent->Health = MaxHealth;

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
	
	AAIController* AIController = Cast<AAIController>(GetController());
	AIController->MoveToLocation(PlayerPawn->GetActorLocation(), AcceptableRadius);
	
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
	// Debug
	UE_LOG(LogTemp, Warning, TEXT("%f"), Cast<UHealthComponent>( GetComponentByClass(UHealthComponent::StaticClass()))->Health);
}

void AEnemy::Reload()
{
	CanAttack = true;
	GetWorldTimerManager().ClearTimer(TimerHandle);
}