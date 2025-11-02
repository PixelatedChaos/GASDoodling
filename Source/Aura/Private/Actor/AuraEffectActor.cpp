// Copyright Kyle Lautenbach 2025


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"



AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;	

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, FAppliedEffectData InGameplayEffectData) 
{
	checkf(InGameplayEffectData.GameplayEffectClass, TEXT("Attempting to apply non-existent gameplay effect class!"));
	
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC)
	{
		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(InGameplayEffectData.GameplayEffectClass, 1.0f, EffectContextHandle);
		const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

		const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
		
		if (bIsInfinite && InGameplayEffectData.InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
		}		
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	for (FAppliedEffectData EffectCandidate : AppliedEffects)
	{
		if (EffectCandidate.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, EffectCandidate);
		}
	}

	if (ActorDestructionPolicy == EActorDestructionPolicy::DestroyOnOverlap)
	{
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	for (FAppliedEffectData EffectCandidate : AppliedEffects)
	{
		if (EffectCandidate.EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, EffectCandidate);
		}
	
		if (EffectCandidate.InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
			if (!IsValid(TargetASC)) return;

			TArray<FActiveGameplayEffectHandle> HandlesToRemove;
			for (auto HandlePair : ActiveEffectHandles)
			{
				if (TargetASC == HandlePair.Value)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
					HandlesToRemove.Add(HandlePair.Key);
				}
			}

			for (auto& Handle : HandlesToRemove)
			{
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
		}
	}	

	if (ActorDestructionPolicy == EActorDestructionPolicy::DestroyOnEndOverlap)
	{
		Destroy();
	}
}

