#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "I_interaction.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPPROJECT_API UI_interaction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UI_interaction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Interaction")
	float TraceDistance = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "CurrentItem")
	AActor* CurrentItem;
	
	void Interact(AActor* actor);
};
