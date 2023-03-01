// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerPawn.h"
#include "CannonWeaponGear.h"
#include "DeathScreenUI.h"
#include "ElectroFieldGear.h"
#include "Enemy.h"
#include "LevelUpUI.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "ExperienceCrystal.h"
#include "ExperienceSystem.h"
#include "HealthComponent.h"
#include "MovementGear.h"
#include "PlayerHUDUI.h"
#include "ShurikensGear.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ElectroField = CreateDefaultSubobject<UElectroFieldGear>(TEXT("ElectroField"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating"));
	ExperienceSystem = CreateDefaultSubobject<UExperienceSystem>(TEXT("Experience System"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Cannon = CreateDefaultSubobject<UCannonWeaponGear>(TEXT("Cannon"));
	Shurikens = CreateDefaultSubobject<UShurikensGear>(TEXT("Shurikens"));
	ShurikensPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	MovementGear = CreateDefaultSubobject<UMovementGear>(TEXT("Movement"));
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
	
	RootComponent = CapsuleComponent;
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);
	BaseMesh->SetupAttachment(CapsuleComponent);
	Shurikens->ShurikensPivot = ShurikensPivot;
	ShieldMesh->SetupAttachment(BaseMesh);

	EquipmentList.Add("Cannon");
	EquipmentList.Add("Shurikens");
	EquipmentList.Add("ElectroField");
	EquipmentList.Add("Health");
	EquipmentList.Add("Movement");
}


// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	ShieldMesh->AddLocalOffset(FVector(0, 0, 50));
	//FloatingPawnMovement->MaxSpeed = 50;
	ShurikensPivot->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	if(HealthComponent)
	{
		HealthComponent->Health = HealthComponent->MaxHealth;

		if (BaseMaterial && OnDamageMaterial)
		{
			HealthComponent->BaseMaterial = BaseMaterial;
			HealthComponent->OnDamageMaterial = OnDamageMaterial;
		}
		else UE_LOG(LogTemp, Error, TEXT("APlayerPawn: One or both Materials for HealthComponent is not set"));
	}
	
	if(ShieldMesh)
	{
		ShieldMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		ShieldMesh->SetRelativeLocation(FVector(0,0,-130));
		ShieldMesh->SetVisibility(false);
		HealthComponent->ShieldMeshRef = ShieldMesh;
	}
	else UE_LOG(LogTemp, Error, TEXT("Shield mesh is not set!"));

	PlayerHudui = CreateWidget<UPlayerHUDUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), PlayerHUDUIClass);
	PlayerHudui->SetReferences(&HealthComponent->Health, &HealthComponent->Shield, &ExperienceSystem->ExperiencePoints, &ExperienceSystem->ExpToNextLevel, &ExperienceLevel);
	PlayerHudui->AddToPlayerScreen();
	PlayerHudui->SetLevelTimerReferences(MinutesRef, SecondsRef);
	//ShieldGear->Shield = 10;
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);
	for (AActor* OverlappingActor : OverlappingActors)
	{
		if(OverlappingActor->IsA(AExperienceCrystal::StaticClass()))
		{
			ExperienceSystem->AddExp(Cast<AExperienceCrystal>(OverlappingActor)->Experience);
			OverlappingActor->Destroy();
		}
	}
}

// ****************************************************** INPUT ******************************************************

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
		EnhancedInputComponent->BindAction(IADebug1, ETriggerEvent::Started, this, &APlayerPawn::Debug1);
		EnhancedInputComponent->BindAction(IADebug2, ETriggerEvent::Started, this, &APlayerPawn::Debug2);
		EnhancedInputComponent->BindAction(IADebug3, ETriggerEvent::Started, this, &APlayerPawn::Debug3);
		EnhancedInputComponent->BindAction(IADebug4, ETriggerEvent::Started, this, &APlayerPawn::Debug4);
		EnhancedInputComponent->BindAction(IADebug5, ETriggerEvent::Started, this, &APlayerPawn::Debug5);
	}
}

void APlayerPawn::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerPawn::SetMaxSpeed(float NewMaxSpeed)
{
	FloatingPawnMovement->MaxSpeed = NewMaxSpeed;
}

float APlayerPawn::GetMaxSpeed()
{
	return FloatingPawnMovement->MaxSpeed;
}

void APlayerPawn::ShowLevelUpScreen()
{
	if (LevelUpUIClass)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.01);
		LevelUpUI = CreateWidget<ULevelUpUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), LevelUpUIClass);
		LevelUpUI->InitializeReferences(this, HealthComponent, Cannon, Shurikens, ElectroField, MovementGear);
		LevelUpUI->AddToPlayerScreen();
	}
}

void APlayerPawn::ShowDeathScreen()
{
	if(DeathScreenUIClass)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.01);
		auto DeathScreen = CreateWidget<UDeathScreenUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), DeathScreenUIClass);
		DeathScreen->AddToPlayerScreen();
	}
	
}

void APlayerPawn::Die()
{
	ShowDeathScreen();
	if(HealthComponent->Health <0) HealthComponent->Health = 0;
	Destroy();
}

void APlayerPawn::Debug1(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Debug 1")));
	ShowLevelUpScreen();
}

void APlayerPawn::Debug2(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Debug 2")));
}

void APlayerPawn::Debug3(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Debug 3")));
}

void APlayerPawn::Debug4(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Debug 4")));
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
}

void APlayerPawn::Debug5(const FInputActionValue& Value)
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), UGameplayStatics::GetGlobalTimeDilation(GetWorld()) + 0.5 );
	UE_LOG(LogTemp, Warning, TEXT("Time Dilation set to: %f"), UGameplayStatics::GetGlobalTimeDilation(GetWorld()));
}
