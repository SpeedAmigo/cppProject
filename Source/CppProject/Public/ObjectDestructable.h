// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat.h"
#include "GameFramework/Actor.h"
#include "ObjectDestructable.generated.h"

class UAttributes;

UCLASS()
class CPPPROJECT_API AObjectDestructable : public AActor, public ICombat
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectDestructable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Basic")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VIsibleAnywhere, BlueprintReadWrite, Category = "Attribute")
	UAttributes* Attributes;

	void GetHit_Implementation(int damage);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
