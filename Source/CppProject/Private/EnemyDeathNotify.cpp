// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDeathNotify.h"

#include "EnemyBaseCharacter.h"

void UEnemyDeathNotify::Notify(USkeletalMeshComponent* MeshComp,
                               UAnimSequenceBase* Animation,
                               const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp) return;
	if (AEnemyBaseCharacter* Enemy = Cast<AEnemyBaseCharacter>(MeshComp->GetOwner()))
	{
		Enemy->Die(); // finalize death (destroy, ragdoll, etc.)
	}
}
