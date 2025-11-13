// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class CPPPROJECT_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	UBoxComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bShowDebugTrace = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	USceneComponent* TraceStart;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	USceneComponent* TraceEnd;
	
	UPROPERTY()
	TArray<AActor*> HitActors;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Pick_Up(AActor* actor) override;

	void DetectCollision(bool value);
	void BoxTrace(FHitResult& OutHit);
	void OnHit(const FHitResult& HitResult);
	void PerformBoxTrace();
	void ClearHitActors();
};
