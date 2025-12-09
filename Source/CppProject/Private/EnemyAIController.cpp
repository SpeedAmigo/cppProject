// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "ABaseEnemyCharacter.h"
#include "BaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Misc/LowLevelTestAdapter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"

const FName AEnemyAIController::CanSeePlayer(TEXT("CanSeePlayer"));
const FName AEnemyAIController::TargetActor(TEXT("TargetActor"));
const FName AEnemyAIController::LastKnownPlayerlocation(TEXT("LastKnownPlayerlocation"));

AEnemyAIController::AEnemyAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1100.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());

	UE_LOG(LogTemp, Log, TEXT("SightRadius = %f (cm), LoseSightRadius = %f (cm)"), SightConfig->SightRadius, SightConfig->LoseSightRadius);

	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	EnemyPawn = Cast<ABaseCharacter>(GetPawn());
	
	if (BehaviorTreeAsset)
	{
		InitializeBlackboard();
		RunBehaviorTree(BehaviorTreeAsset);
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Visual debug draw: show sight radii at pawn location
	APawn* MyPawn = GetPawn();
	if (MyPawn && SightConfig)
	{
		const FVector Loc = MyPawn->GetActorLocation();

		// Sight radius (green)
		DrawDebugSphere(GetWorld(), Loc, SightConfig->SightRadius, 32, FColor::Green, true /*persistent*/, -1.f /*life*/, 0 /*depthPriority*/, 2.f /*thickness*/);

		// Lose sight radius (red)
		DrawDebugSphere(GetWorld(), Loc, SightConfig->LoseSightRadius, 32, FColor::Red, true, -1.f, 0, 2.f);
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
		BlackboardComp->SetValueAsBool(CanSeePlayer, true);
		UE_LOG(LogTemp, Display, TEXT("Sensed Player"));

		if (EnemyPawn)
		{
			EnemyPawn->State = PawnState::InCombat;
		}
	}
	else
	{
		BlackboardComp->SetValueAsObject(TargetActor, nullptr);

		if (Actor)
		{
			BlackboardComp->SetValueAsVector(LastKnownPlayerlocation, Actor->GetActorLocation());
		}

		if (EnemyPawn)
		{
			EnemyPawn->State = PawnState::Search;
		}
		
		//BlackboardComp->SetValueAsBool(CanSeePlayer, false);
		
		UE_LOG(LogTemp, Display, TEXT("Cannot see the player"));
	}
}
