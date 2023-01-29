// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "CannonWeaponGear.h"
#include "PlayerPawn.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = BaseMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement component"));

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::DestroyProjectile, 1, false, TimeToDestroy);
	BaseMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnCollisionBegin);

	WeaponGear = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->FindComponentByClass<UCannonWeaponGear>();
	
	Penetration =  WeaponGear->Penetration;
	Damage = WeaponGear->Damage;
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AProjectile::DestroyProjectile()
{
	Destroy();
}

void AProjectile::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	auto DamageTypeClass = UDamageType::StaticClass();
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, DamageTypeClass);
	
	Penetration--;
	if(Penetration <= 0) DestroyProjectile();
}
