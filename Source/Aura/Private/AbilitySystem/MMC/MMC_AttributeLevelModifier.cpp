// Copyright Kyle Lautenbach 2025


#include "AbilitySystem/MMC/MMC_AttributeLevelModifier.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_AttributeLevelModifier::UMMC_AttributeLevelModifier()
{
	
}

float UMMC_AttributeLevelModifier::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float BaseMagnitude = 0.f;
	//Get first attribute definition
	checkf(!GetAttributeCaptureDefinitions().IsEmpty(),TEXT("MMC missing attribute definition in %s!"), *this->GetName());
	const FGameplayEffectAttributeCaptureDefinition CapturedAttributeDef = GetAttributeCaptureDefinitions()[0];
	if (CapturedAttributeDef.AttributeToCapture.IsValid())
	{		
		GetCapturedAttributeMagnitude(CapturedAttributeDef, Spec, EvaluationParameters, BaseMagnitude);
		BaseMagnitude = FMath::Max<float>(BaseMagnitude,0.f);

		ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
		if (CombatInterface)
		{
			const int32 EntityLevel = CombatInterface->GetEntityLevel();

			return BaseValue + (BaseMagnitude * AttributeMultiplier) + (LevelMultiplier * EntityLevel);
		}
	}
	
	return BaseMagnitude;
}
