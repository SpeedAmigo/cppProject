// cpp
#include "MainHUD.h"
#include "BaseCharacter.h"
#include "Attributes.h"
#include "Components/ProgressBar.h"
#include "GameFramework/PlayerController.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();
	InitAttributes();
	if (Attributes)
	{
		// Initialize cached values
		CachedHealth = Attributes->GetHealth();
		CachedStamina = Attributes->GetStamina();

		Attributes->OnHealthChanged.AddDynamic(this, &UMainHUD::HandleHealthChanged);
		Attributes->OnStaminaChanged.AddDynamic(this, &UMainHUD::HandleStaminaChanged);
	}
}

void UMainHUD::NativeDestruct()
{
	if (Attributes)
	{
		Attributes->OnHealthChanged.RemoveDynamic(this, &UMainHUD::HandleHealthChanged);
		Attributes->OnStaminaChanged.RemoveDynamic(this, &UMainHUD::HandleStaminaChanged);
	}
	Super::NativeDestruct();
}



void UMainHUD::InitAttributes()
{
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			if (ABaseCharacter* Char = Cast<ABaseCharacter>(Pawn))
			{
				Attributes = Char->Attributes;
			}
		}
	}
}

void UMainHUD::HandleHealthChanged(int32 NewHealth)
{
	CachedHealth = NewHealth;
	UpdateHealthBar();
}

void UMainHUD::HandleStaminaChanged(float NewStamina)
{
	CachedStamina = NewStamina;
	UpdateStaminaBar();
}

void UMainHUD::UpdateHealthBar()
{
	if (HealthBar)
	{
		float Percent = (Attributes->GetMaxHealth() > 0) ? static_cast<float>(CachedHealth) / Attributes->GetMaxHealth() : 0.f;
		HealthBar->SetPercent(Percent);
	}
}

void UMainHUD::UpdateStaminaBar()
{
	if (StaminaBar)
	{
		float Percent = (Attributes->GetMaxStamina() > 0.f) ? CachedStamina / Attributes->GetMaxStamina() : 0.f;
		StaminaBar->SetPercent(Percent);
	}
}

/*int UMainHUD::HealthUpdate()
{
	return Attributes ? Attributes->GetHealth() : CachedHealth;
}

float UMainHUD::StaminaUpdate()
{
	return Attributes ? Attributes->GetStamina() : CachedStamina;
}*/
