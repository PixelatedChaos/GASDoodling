// Copyright Kyle Lautenbach 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void InitOverlay(const FWidgetControllerParams WCParams);
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
};
