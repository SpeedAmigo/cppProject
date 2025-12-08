#pragma once

#include "CoreMinimal.h"

UENUM()
enum class PawnState
{
	Idle UMETA(DisplayName = "Idle"),
	InCombat UMETA(DisplayName = "InCombat"),
	Occupied UMETA(DisplayName = "Occupied"),
	Dead UMETA(DisplayName = "Dead"),
	Exhausted UMETA(DisplayName = "Exhausted"),
};
