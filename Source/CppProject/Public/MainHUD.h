// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class CPPPROJECT_API UMainHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float Current, float Max);

	UFUNCTION(BlueprintCallable)
	void UpdateStamina(float Current, float Max);
};
