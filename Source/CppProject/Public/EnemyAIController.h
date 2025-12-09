// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;
class UBehaviorTreeComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class ABaseCharacter;
/**
 * 
 */
UCLASS()
class CPPPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();
	void GetHit();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	bool InitializeBlackboard();

	UPROPERTY()
	ABaseCharacter* EnemyPawn;

	UPROPERTY(EditDefaultsOnly, Category = "BehaviourTree")
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComp;
	
	// Perception
	UPROPERTY(VisibleAnywhere, Category = "AI")
	UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	UAISenseConfig_Sight* SightConfig;

	// Blackboard key names
	static const FName CanSeePlayer;
	static const FName TargetActor;
	static const FName LastKnownPlayerlocation;

	// Perception callback
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
