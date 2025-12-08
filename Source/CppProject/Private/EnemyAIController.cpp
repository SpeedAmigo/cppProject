// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorComp  = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTreeAsset)
	{
		InitializeBlackboard();
		RunBehaviorTree(BehaviorTreeAsset);
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

bool AEnemyAIController::InitializeBlackboard()
{
	if (BehaviorTreeAsset && BehaviorTreeAsset->BlackboardAsset)
	{
		UseBlackboard(BehaviorTreeAsset->BlackboardAsset, BlackboardComp);
		return true;
	}
	return false;
}
