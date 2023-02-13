// Fill out your copyright notice in the Description page of Project Settings.


#include "ShurikenProjectile.h"

#include "PlayerPawn.h"
#include "ShurikensGear.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShurikenProjectile::AShurikenProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shuriken Mesh"));

	RootComponent = BaseMesh;

}

// Called when the game starts or when spawned
void AShurikenProjectile::BeginPlay()
{
	Super::BeginPlay();
	Damage = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->Shurikens->Damage;

	if (BaseMesh)
	{
		BaseMesh->OnComponentBeginOverlap.AddDynamic(this, &AShurikenProjectile::OnCollisionBegin);
	}
}

// Called every frame
void AShurikenProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0, RotationSpeed * DeltaTime, 0));
}

void AShurikenProjectile::OnCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	const auto DamageTypeClass = UDamageType::StaticClass();
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, DamageTypeClass);
}

