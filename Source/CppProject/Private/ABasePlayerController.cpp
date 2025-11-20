// Source/CppProject/Private/ABasePlayerController.cpp
#include "ABasePlayerController.h"

#include "MainHUD.h"
#include "Blueprint/UserWidget.h"

void AABasePlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (MainHUDClass)
    {
        MainHUDInstance = CreateWidget<UMainHUD>(this, MainHUDClass);
        if (MainHUDInstance)
        {
            MainHUDInstance->AddToViewport();
        }
    }
}
