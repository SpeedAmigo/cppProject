// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes.h"

// Sets default values for this component's properties
UAttributes::UAttributes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttributes::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}


// Called every frame
void UAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAttributes::SetHealth(int32 NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0, MaxHealth);
}

void UAttributes::SetMaxHealth(int32 NewMaxHealth)
{
	MaxHealth = FMath::Max(NewMaxHealth, 1);
}


