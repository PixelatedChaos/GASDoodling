// Copyright Kyle Lautenbach 2025


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(const FWidgetControllerParams WCParams)
{
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninitialised. Check that it is set in BP_AuraHUD."));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninitialised. Check that it is set in BP_AuraHUD."));
	
	OverlayWidget = CreateWidget<UAuraUserWidget>(GetWorld(), OverlayWidgetClass);
	checkf(OverlayWidget, TEXT("OverlayWidgetClass not of correct type (AuraUserWidget)."));
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WCParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	
	OverlayWidget->AddToViewport();
}


