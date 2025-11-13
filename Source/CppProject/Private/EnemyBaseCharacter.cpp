// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"

#include "ABasePlayerCharacter.h"
#include "Attributes.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
	SphereComponent->SetupAttachment(RootComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBaseCharacter::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyBaseCharacter::OnSphereEndOverlap);
	
	Attributes = CreateDefaultSubobject<UAttributes>(TEXT("Attributes"));
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	PawnState = PawnState::Idle;
}

void AEnemyBaseCharacter::GetHit_Implementation(int damage)
{
	PawnState = PawnState::Occupied;
	
	int Health = Attributes->GetHealth();
	
	Health -= damage;

	if (Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Object Destroyed"));

		PlayAnimMontage(DieMontage);
		
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

void AEnemyBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEnemyBaseCharacter::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	if (AABasePlayerCharacter* Player = Cast<AABasePlayerCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Log, TEXT("Player enter: %s"), *OtherActor->GetName());
		OverlappingActors.Add(OtherActor);
		PawnState = PawnState::InCombat;
		PlayAnimMontage(AttackMontage);
	}
}

void AEnemyBaseCharacter::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || OtherActor == this) return;

	if (AABasePlayerCharacter* Player = Cast<AABasePlayerCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Log, TEXT("Player exit: %s"), *OtherActor->GetName());
		OverlappingActors.Remove(OtherActor);
	}

	PawnState = PawnState::Idle;
}

void AEnemyBaseCharacter::Die()
{
	Destroy();
}
