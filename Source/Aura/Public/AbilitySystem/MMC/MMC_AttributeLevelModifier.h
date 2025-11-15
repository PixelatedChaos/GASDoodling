// Copyright Kyle Lautenbach 2025

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_AttributeLevelModifier.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class AURA_API UMMC_AttributeLevelModifier : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UMMC_AttributeLevelModifier();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	UPROPERTY(EditAnywhere, Category = "Calculation Parameters")
	FGameplayEffectAttributeCaptureDefinition AttributeDef;
	UPROPERTY(EditAnywhere, Category = "Calculation Parameters")
	float BaseValue = 10.f;
	UPROPERTY(EditAnywhere, Category = "Calculation Parameters")
	float AttributeMultiplier = 1.0f;
	UPROPERTY(EditAnywhere, Category = "Calculation Parameters")
	float LevelMultiplier = 10.f;
};
