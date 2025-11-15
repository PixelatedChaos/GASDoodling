// Copyright Kyle Lautenbach 2025


#include "AbilitySystem/MMC/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"


UMMC_MaxHealth::UMMC_MaxHealth()
{
	 BaseValue = 80.f;
	 AttributeMultiplier = 2.5f;	
	 LevelMultiplier = 10.f;
}
