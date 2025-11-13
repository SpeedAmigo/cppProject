// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"
#include "Attributes.h"
#include "Kismet/GameplayStatics.h"


AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	Attributes = CreateDefaultSubobject<UAttributes>(TEXT("Attributes"));
}

void AEnemyBaseCharacter::GetHit_Implementation(int damage)
{
	int Health = Attributes->GetHealth();
	
	Health -= damage;

	if (Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Object Destroyed"));

		PlayAnimMontage(DieAnim);
		
		if (DieSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DieSound, GetActorLocation());
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Object Hitted"));
		Attributes->SetHealth(Health);
		PlayAnimMontage(GettingHitMontage);

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
	}
}

void AEnemyBaseCharacter::Die()
{
	Destroy();
}
