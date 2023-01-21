// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating"));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComponent;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	HealthPoints = MaxHealthPoints;

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
				
			}
		}
	}
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleHealth();

}

void APlayerPawn::HandleHealth()
{
	UE_LOG(LogTemp, Display, TEXT("%f"), HealthPoints);
	if (HealthPoints <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, (TEXT("U DED")));
		
		//TODO Death procedure
	}
}

// ****************** INPUT ******************

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

void APlayerPawn::Debug1(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Debug 1")));

	HealthPoints--;
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
}

void APlayerPawn::Debug5(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, (TEXT("Debug 5")));
}
