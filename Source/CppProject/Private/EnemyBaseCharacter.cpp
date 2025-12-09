// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"

#include "ABasePlayerCharacter.h"
#include "Attributes.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"


AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	State = PawnState::Patrol;
}

void AEnemyBaseCharacter::GetHit_Implementation(int damage)
{
	State = PawnState::Occupied;
	
	int Health = Attributes->GetHealth();
	
	Health -= damage;

	if (Health <= 0)
	{
		State = PawnState::Dead;
		UE_LOG(LogTemp, Warning, TEXT("Object Destroyed"));

		PlayAnimMontage(DieMontage);
		
		if (DieSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DieSound, GetActorLocation());
		}
	}
	else
	{
		State = PawnState::Occupied;
		UE_LOG(LogTemp, Display, TEXT("Object Hitted"));
		Attributes->SetHealth(Health);
		
		PlayAnimMontage(GettingHitMontage);

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
	}
}

void AEnemyBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyBaseCharacter::Die()
{
	Destroy();
}

void AEnemyBaseCharacter::AttackPlayer()
{
	if (Attributes->CanPayStaminaCost(Attributes->StaminaCosts.StaminaCost_Attack))
	{
		Attributes->PayStamina(Attributes->StaminaCosts.StaminaCost_Attack);
		PlayAnimMontage(AttackMontage);
	}
	UE_LOG(LogTemp, Log, TEXT("Enemy Attacks"))
}

PawnState AEnemyBaseCharacter::ChangeState(PawnState value)
{
	State = value;
	return value;
}
