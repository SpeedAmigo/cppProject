// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"

const FName AEnemyAIController::CanSeePlayer(TEXT("CanSeePlayer"));
const FName AEnemyAIController::TargetActor(TEXT("TargetActor"));

AEnemyAIController::AEnemyAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	BehaviorComp  = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 2000.f;
	SightConfig->LoseSightRadius = 2200.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());

	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
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
	UE_LOG(LogTemp, Log, TEXT("AEnemyAIController::OnPossess called for %s"), *GetNameSafe(InPawn));

	if (!BehaviorTreeAsset)
	{
		UE_LOG(LogTemp, Warning, TEXT("BehaviorTreeAsset not assigned on %s - blackboard won't be initialized"), *GetNameSafe(this));
		return;
	}

	if (InitializeBlackboard())
	{
		UE_LOG(LogTemp, Log, TEXT("Blackboard initialized on %s"), *GetNameSafe(this));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to initialize blackboard on %s"), *GetNameSafe(this));
	}

	// start the behavior tree for this pawn
	if (!RunBehaviorTree(BehaviorTreeAsset))
	{
		UE_LOG(LogTemp, Warning, TEXT("RunBehaviorTree failed on %s"), *GetNameSafe(this));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Behavior tree started on %s"), *GetNameSafe(this));
	}
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

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!BlackboardComp) return;

	const bool bSensed = Stimulus.WasSuccessfullySensed();
	BlackboardComp->SetValueAsBool(CanSeePlayer, bSensed);

	if (bSensed)
	{
		BlackboardComp->SetValueAsObject(TargetActor, Actor);
		UE_LOG(LogTemp, Display, TEXT("Sensed Player"));
	}
	else
	{
		BlackboardComp->SetValueAsObject(TargetActor, nullptr);
		UE_LOG(LogTemp, Display, TEXT("Cannot see the player"));
	}
}
