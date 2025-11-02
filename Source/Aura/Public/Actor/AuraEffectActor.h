// Copyright Kyle Lautenbach 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UENUM(BlueprintType)
enum class EActorDestructionPolicy : uint8
{
	DestroyOnOverlap,
	DestroyOnEndOverlap,
	DoNotDestroy
};

USTRUCT(BlueprintType)
struct FAppliedEffectData
{
	GENERATED_BODY()
	FAppliedEffectData(){}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::ApplyOnOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAuraEffectActor();

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void ApplyEffectToTarget(AActor* TargetActor, FAppliedEffectData InGameplayEffectData);

	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable, Category = "Applied Effects")
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TArray<FAppliedEffectData> AppliedEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	EActorDestructionPolicy ActorDestructionPolicy = EActorDestructionPolicy::DoNotDestroy;

	UPROPERTY(BlueprintReadOnly, Category = "Applied Effects")
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

private:
};
