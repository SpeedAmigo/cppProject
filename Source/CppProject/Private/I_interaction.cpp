#include "I_interaction.h"

#include "Interactable.h"

// Sets default values for this component's properties
UI_interaction::UI_interaction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UI_interaction::BeginPlay()
{
	Super::BeginPlay();
}

void UI_interaction::Interact(AActor* actor)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) return;

	FVector Location;
	FRotator Rotation;
	PlayerController->GetPlayerViewPoint(Location, Rotation);

	FVector Start = Location;
	FVector End = Start + (Rotation.Vector() * TraceDistance);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		TraceParams
		);

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.f, 0.f, 1.f);
	
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{
				IInteractable::Execute_Interact(HitActor, GetOwner());

				CurrentItem = HitActor;
				UE_LOG(LogTemp, Warning, TEXT("Interacted with %s"), *HitActor->GetName());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing hit"));
	}
}

