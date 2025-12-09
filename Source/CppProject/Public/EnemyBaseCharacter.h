// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Combat.h"
#include "EnemyBaseCharacter.generated.h"

class AEnemyAIController;
/**
 * 
 */

UCLASS()
class CPPPROJECT_API AEnemyBaseCharacter : public ABaseCharacter, public ICombat
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* AttackMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* GettingHitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
	UAnimMontage* DieMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* DieSound;
	
	UFUNCTION()
	void Die();

	UFUNCTION(BlueprintCallable)
	void AttackPlayer();

	UFUNCTION(BlueprintCallable)
	PawnState ChangeState(PawnState value);
	
protected:

	AEnemyBaseCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	void GetHit_Implementation(int damage);
	
	UPROPERTY()
	TSet<AActor*> OverlappingActors;
};
