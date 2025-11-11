// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "ABasePlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Pick_Up(AActor* actor)
{
	AABasePlayerCharacter* Character = Cast<AABasePlayerCharacter>(actor);
	if (!Character)
	{
		UE_LOG(LogTemp, Display, TEXT("No character found"));
		return;
	}

	const FName SocketName = TEXT("rHSocket");

	FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh(), Rules, SocketName);

	SetActorEnableCollision(false);
	
	UE_LOG(LogTemp, Display, TEXT("Pick Up"));
}

void AWeapon::DetectCollision(bool value)
{
}


