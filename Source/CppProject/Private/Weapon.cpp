// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "ABasePlayerCharacter.h"
#include "Combat.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	Mesh->SetupAttachment(RootComponent);	
	
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Collider->SetupAttachment(Mesh);

	TraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("TraceStart"));
	TraceStart->SetupAttachment(Mesh);

	TraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("TraceEnd"));
	TraceEnd->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	//Collider = Cast<UBoxComponent>(GetDefaultSubobjectByName(TEXT("BoxCollision")));
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
	
	SetOwner(Character);
	
	SetActorEnableCollision(false);
	
	UE_LOG(LogTemp, Display, TEXT("Pick Up"));
}

void AWeapon::DetectCollision(bool value)
{
	if (!Collider)
	{
		UE_LOG(LogTemp, Warning, TEXT("No BoxCollider"));
		return;
	}

	if (value)
	{
		Collider->SetCollisionEnabled(value? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	}
}

void AWeapon::BoxTrace(FHitResult& OutHit)
{
	if (!TraceStart || !TraceEnd || !Collider) return;

	const FVector Start = TraceStart->GetComponentLocation();
	const FVector End = TraceEnd->GetComponentLocation();
	
	// Pobierz wymiary box collider z SwordHitbox
	const FVector BoxExtent = Collider->GetScaledBoxExtent();
	
	// Pobierz rotacjê z SwordHitbox (zamiast z TraceStart)
	const FRotator BoxRotation = Collider->GetComponentRotation();
	
	// Ustawienie kana³ów kolizji do ignorowania
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	if (AActor* WeaponOwner = GetOwner())
	{
		ActorsToIgnore.Add(WeaponOwner);
	}
	
	// Dodaj wszystkich ju¿ trafionych aktorów do ignorowania
	ActorsToIgnore.Append(HitActors);

	// Wykonanie box trace z wymiarami SwordHitbox
	const bool bHit = UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		BoxExtent,
		BoxRotation,
		UEngineTypes::ConvertToTraceType(ECC_Pawn),
		false,
		ActorsToIgnore,
		bShowDebugTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None,
		OutHit,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		2.0f
	);

	if (bHit && OutHit.GetActor())
	{
		// Dodaj trafionego aktora do listy
		HitActors.AddUnique(OutHit.GetActor());
		OnHit(OutHit);
	}
}

void AWeapon::OnHit(const FHitResult& HitResult)
{
	// Logowanie miejsca zderzenia
	if (AActor* HitActor = HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon hit: %s at location: %s"), 
			*HitResult.GetActor()->GetName(), 
			*HitResult.ImpactPoint.ToString());

		//AActor* HitActor = HitResult.GetActor();
		//if (!HitActor) return;
		if (HitActor->GetClass()->ImplementsInterface(UCombat::StaticClass()))
		{
			ICombat::Execute_GetHit(HitActor, Damage);
		}
	}
}

void AWeapon::PerformBoxTrace()
{
	FHitResult HitResult;
	BoxTrace(HitResult);
}

void AWeapon::ClearHitActors()
{
	HitActors.Empty();
}

