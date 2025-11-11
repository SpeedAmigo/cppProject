// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "BaseCharacter.h"
#include "ABasePlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
class UI_interaction;

UCLASS()
class CPPPROJECT_API AABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	AABasePlayerCharacter();

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	void Interact();
	void Attack();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool IsAttacking;

private:

	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere)
	UCameraComponent* ViewCamera;

	// Interaction component that handles interaction logic (trace, interface calls)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta=(AllowPrivateAccess="true"))
	UI_interaction* InteractionComponent;

};