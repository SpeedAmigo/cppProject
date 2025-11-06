// Fill out your copyright notice in the Description page of Project Settings.


#include "I_interaction.h"

// Sets default values for this component's properties
UI_interaction::UI_interaction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UI_interaction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UI_interaction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

