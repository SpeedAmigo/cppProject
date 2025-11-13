// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Combat.h"
#include "EnemyBaseCharacter.generated.h"

/**
 * 
 */
class UAttributes;

UCLASS()
class CPPPROJECT_API AEnemyBaseCharacter : public ABaseCharacter, public ICombat
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basics", meta = (AllowPrivateAccess = "true"))
	UAttributes* Attributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* GettingHitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* DieAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* DieSound;

	UFUNCTION()
	void Die();
	
protected:

	AEnemyBaseCharacter();

	void GetHit_Implementation(int damage);

private:
	

};
