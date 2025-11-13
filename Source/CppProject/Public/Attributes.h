// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaminaCosts.h"
#include "Components/ActorComponent.h"
#include "Attributes.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPPROJECT_API UAttributes : public UActorComponent
{
	GENERATED_BODY()

public:

	// Getters
	UFUNCTION(BlueprintCallable, Category="Health")
	int32 GetHealth() const {return Health;}

	UFUNCTION(BlueprintCallable, Category="Health")
	int32 GetMaxHealth() const {return MaxHealth;}

	UFUNCTION(BlueprintCallable, Category="Stamina")
	float GetStamina() const {return Stamina;}

	UFUNCTION(BlueprintCallable, Category="Stamina")
	float GetMaxStamina() const {return MaxStamina;}

	// Setters
	UFUNCTION(BlueprintCallable, Category="Health")
	void SetHealth(int32 NewHealth);

	UFUNCTION(BlueprintCallable, Category="Health")
	void SetMaxHealth(int32 NewMaxHealth);

	UFUNCTION(BlueprintCallable, Category="Stamina")
	void SetStamina(float NewStamina);

	UFUNCTION(BlueprintCallable, Category="Stamina")
	void SetMaxStamina(float NewMaxStamina);

	UFUNCTION(BlueprintCallable, Category="Stamina")
	bool CanPayStaminaCost(float cost);

	UFUNCTION(BlueprintCallable, Category="Stamina")
	void PayStamina(float cost);
	
	// Sets default values for this component's properties
	UAttributes();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", meta = (AllowPrivateAccess = "true"))
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", meta = (AllowPrivateAccess = "true"))
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina", meta = (AllowPrivateAccess = "true"))
	FStaminaCosts StaminaCosts;
};
