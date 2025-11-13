// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectDestructable.h"
#include "Attributes.h"

// Sets default values
AObjectDestructable::AObjectDestructable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	Mesh->SetupAttachment(RootComponent);

	Attributes = CreateDefaultSubobject<UAttributes>(TEXT("Attributes"));
}

// Called when the game starts or when spawned
void AObjectDestructable::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObjectDestructable::GetHit_Implementation(int damage)
{
	int Health = Attributes->GetHealth();

	Health -= damage;

	if (Health <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Object Destroyed"));
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Object Hitted"));
		Attributes->SetHealth(Health);
	}
}

// Called every frame
void AObjectDestructable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

