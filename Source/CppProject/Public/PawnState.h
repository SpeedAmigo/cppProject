#pragma once

#include "CoreMinimal.h"

UENUM()
enum class PawnState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Patrol UMETA(DisplayName = "Patrol"),
	Search UMETA(DisplayName = "Search"),
	InCombat UMETA(DisplayName = "InCombat"),
	Occupied UMETA(DisplayName = "Occupied"),
	Dead UMETA(DisplayName = "Dead"),
	Exhausted UMETA(DisplayName = "Exhausted"),
};
