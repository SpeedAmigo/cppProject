// cpp
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

class UProgressBar;
class UAttributes;

UCLASS()
class CPPPROJECT_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;
	
	/*// Slider bindings in Blueprint can call these
	UFUNCTION(BlueprintCallable)
	int HealthUpdate();

	UFUNCTION(BlueprintCallable)
	float StaminaUpdate();*/

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void UpdateHealthBar();
	void UpdateStaminaBar();

private:
	// Cached pointer to attributes
	UPROPERTY()
	UAttributes* Attributes = nullptr;

	// Cached values (optional for cheap access)
	int CachedHealth = 0;
	float CachedStamina = 0.f;

	// Delegate handlers
	UFUNCTION()
	void HandleHealthChanged(int32 NewHealth);

	UFUNCTION()
	void HandleStaminaChanged(float NewStamina);

	// Helper to acquire attributes from owning pawn
	void InitAttributes();
};
