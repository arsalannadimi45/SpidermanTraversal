// Fill out your copyright notice in the Description page of Project Settings.

#include "SpidermanTraversal/Player/SpidermanCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpidermanTraversal/Player/SpidermanController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "SpidermanTraversal/Player/InputSystem/InputConfigData.h"

// Sets default values
ASpidermanCharacter::ASpidermanCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Initializing spring arm component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent); 
	SpringArmComponent->SetUsingAbsoluteRotation(false);
	SpringArmComponent->TargetArmLength = 600.f;
	SpringArmComponent->SocketOffset = FVector(75.f, 0, 0);
	SpringArmComponent->SetRelativeRotation(FRotator(0.f, 0, 0.f)); 
	SpringArmComponent->bUsePawnControlRotation = true;

	//Initializing camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
}

// Called when the game starts or when spawned
void ASpidermanCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpidermanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpidermanCharacter::Move(const FInputActionValue& Value)
{
	if (Controller)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

		// Forward/Backward Direction 
		if (MoveValue.Y != 0.f)
		{
			// Get forward vector
			const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

			AddMovementInput(Direction, MoveValue.Y);
		}
		// Right/Left direction
		if (MoveValue.X != 0.f)
		{
			// Get right vector
			const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(Direction, MoveValue.X);
		}
	}
}

void ASpidermanCharacter::Look(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		const FVector2D LookValue = Value.Get<FVector2D>();

		if (LookValue.X != 0.f)
		{
			AddControllerYawInput(LookValue.X);
		}

		if (LookValue.Y != 0.f)
		{
			AddControllerPitchInput(LookValue.Y);
		}
	}
}

// Called to bind functionality to input
void ASpidermanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	// Get the player controller
	APlayerController* PlayerController = Cast<ASpidermanController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings(); 
	Subsystem->AddMappingContext(InputMapping, 0);

	
	// Get the EnhancedInputComponent  (PEI = PlayerEnhancedInput)
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Bind the actions 
	PEI->BindAction(InputActions->Movement_IA, ETriggerEvent::Triggered, this, &ASpidermanCharacter::Move);
	PEI->BindAction(InputActions->Look_IA, ETriggerEvent::Triggered, this, &ASpidermanCharacter::Look);


}

