// Fill out your copyright notice in the Description page of Project Settings.


#include "SetWeaponHitbox.h"

#include "BaseCharacter.h"
#include "Weapon.h"

class ABaseCharacter;

void USetWeaponHitbox::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp) return;

	// Pobierz w�a�ciciela SkeletalMeshComponent (powinien to by� Character)
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	// Sprawd� czy w�a�ciciel to AMyBaseCharacter
	ABaseCharacter* Character = Cast<ABaseCharacter>(Owner);
	if (!Character) return;

	// Pobierz ekwipowan� bro�
	AWeapon* Weapon = Character->EquippedWeapon;
	if (!Weapon) return;

	// Wyczy�� list� trafionych aktor�w przed rozpocz�ciem nowego ataku
	Weapon->ClearHitActors();
	
	// W��cz hitbox broni
	Weapon->DetectCollision(true);
	//UE_LOG(LogTemp, Warning, TEXT("SetWeaponHitbox Notify - Hitbox enabled and hit actors cleared for %s"), *Character->GetName());
}

void USetWeaponHitbox::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp) return;

	// Pobierz w�a�ciciela SkeletalMeshComponent (powinien to by� Character)
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	// Sprawd� czy w�a�ciciel to AMyBaseCharacter
	ABaseCharacter* Character = Cast<ABaseCharacter>(Owner);
	if (!Character) return;

	// Pobierz ekwipowan� bro�
	AWeapon* Weapon = Character->EquippedWeapon;
	if (!Weapon) return;

	// Wy��cz hitbox broni
	Weapon->DetectCollision(false);
	//UE_LOG(LogTemp, Warning, TEXT("SetWeaponHitbox Notify - Hitbox disabled for %s"), *Character->GetName());
}

void USetWeaponHitbox::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!MeshComp) return;

	// Pobierz w�a�ciciela SkeletalMeshComponent (powinien to by� Character)
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	// Sprawd� czy w�a�ciciel to AMyBaseCharacter
	ABaseCharacter* Character = Cast<ABaseCharacter>(Owner);
	if (!Character) return;

	// Pobierz ekwipowan� bro�
	AWeapon* Weapon = Character->EquippedWeapon;
	if (!Weapon) return;

	// Wykonuj box trace co klatk� podczas trwania animacji ataku
	Weapon->PerformBoxTrace();
}