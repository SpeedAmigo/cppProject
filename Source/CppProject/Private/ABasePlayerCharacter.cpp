// Fill out your copyright notice in the Description page of Project Settings.


#include "ABasePlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "I_interaction.h"


AABasePlayerCharacter::AABasePlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom -> SetupAttachment(GetRootComponent());
	CameraBoom -> TargetArmLength = 150.f;
	CameraBoom -> bUsePawnControlRotation = true;
	
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera -> SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ViewCamera -> bUsePawnControlRotation = false;
	
	// Create interaction component
	InteractionComponent = CreateDefaultSubobject<UI_interaction>(TEXT("InteractionComponent"));
}

void AABasePlayerCharacter::Move(const FInputActionValue& InputActionValue)
{
	FVector2D MoveValue = InputActionValue.Get<FVector2D>();

	if (Controller)
	{
		const FRotator YawRotation(0, Controller->GetControlRotation().Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MoveValue.Y);
		AddMovementInput(RightDirection, MoveValue.X);
	}
}

void AABasePlayerCharacter::Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookValue = InputActionValue.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookValue.X);
		AddControllerPitchInput(-LookValue.Y);
	}
}

void AABasePlayerCharacter::Interact() 
{
	// Forward interaction to the interaction component if available
	if (InteractionComponent)
	{
		InteractionComponent->Interact(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact called but InteractionComponent is null"));
	}
}

void AABasePlayerCharacter::Attack()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
	}
}

void AABasePlayerCharacter::AttackStart()
{
	AActor* Weapon = InteractionComponent->CurrentItem;
	
	if (!Weapon) return;
	
	Weapon->SetActorEnableCollision(true);
	
	UE_LOG(LogTemp, Warning, TEXT("Attack Started!"));
}

void AABasePlayerCharacter::AttackEnd()
{
	AActor* Weapon = InteractionComponent->CurrentItem;
	
	if (!Weapon) return;
	
	Weapon->SetActorEnableCollision(false);
	
	UE_LOG(LogTemp, Warning, TEXT("Attack Ended!"));
}

void AABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* Player = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Player->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AABasePlayerCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AABasePlayerCharacter::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		Input->BindAction(InteractAction, ETriggerEvent::Started, this, &AABasePlayerCharacter::Interact);
		Input->BindAction(AttackAction, ETriggerEvent::Started, this, &AABasePlayerCharacter::Attack);
	}
}