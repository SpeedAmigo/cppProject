// Fill out your copyright notice in the Description page of Project Settings.


#include "HitNotify.h"

#include "EnemyAIController.h"
#include "EnemyBaseCharacter.h"

void UHitNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                        const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp) return;
	if (AEnemyAIController* Enemy = Cast<AEnemyAIController>(MeshComp->GetOwner()))
	{
		Enemy->GetHit();
	}
}
