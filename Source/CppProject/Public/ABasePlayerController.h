// Source/CppProject/Public/ABasePlayerController.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ABasePlayerController.generated.h"

class UMainHUD;

UCLASS()
class CPPPROJECT_API AABasePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

protected:
    // Set this in the editor or via code to the UMG widget class (blueprint subclass of UMainHUD)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UMainHUD> MainHUDClass;

    UPROPERTY()
    UMainHUD* MainHUDInstance;
};
