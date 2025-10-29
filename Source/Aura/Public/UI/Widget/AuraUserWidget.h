// Copyright Kyle Lautenbach 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TObjectPtr<UObject> WidgetController;
	

protected:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
