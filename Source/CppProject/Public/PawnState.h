#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class PawnState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	InCombat UMETA(DisplayName = "InCombat"),
	Occupied UMETA(DisplayName = "Occupied"),
};
