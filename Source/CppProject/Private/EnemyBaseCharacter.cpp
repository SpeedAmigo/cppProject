// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"

#include "ABasePlayerCharacter.h"
#include "Attributes.h"
#include "EnemyAIController.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	SphereComponent->SetupAttachment(RootComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBaseCharacter::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyBaseCharacter::OnSphereEndOverlap);

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

/*void AEnemyBaseCharacter::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	if (State == PawnState::Dead || State == PawnState::Occupied) return;

	if (AABasePlayerCharacter* Player = Cast<AABasePlayerCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Log, TEXT("Player enter: %s"), *OtherActor->GetName());
		OverlappingActors.Add(OtherActor);

		if (Attributes->CanPayStaminaCost(Attributes->StaminaCosts.StaminaCost_Attack))
		{
			Attributes->PayStamina(Attributes->StaminaCosts.StaminaCost_Attack);
			PlayAnimMontage(AttackMontage);
		}
	}
}*/

/*void AEnemyBaseCharacter::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || OtherActor == this) return;

	if (AABasePlayerCharacter* Player = Cast<AABasePlayerCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Log, TEXT("Player exit: %s"), *OtherActor->GetName());
		OverlappingActors.Remove(OtherActor);
	}

	//State = PawnState::Idle;
}*/

void AEnemyBaseCharacter::Die()
{
	Destroy();
}

void AEnemyBaseCharacter::GetHit()
{
	State = PawnState::InCombat;
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
