// Copyright Kyle Lautenbach 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"
class UDamageTextComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;
class USplineComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageValue, ACharacter* TargetCharacter);
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	virtual void CursorTrace();
	virtual void AutoRun();

	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bDebugMovementPath = false;

	UPROPERTY(BlueprintReadOnly, Category = "Cursor")
	FHitResult CursorHit;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	UFUNCTION()
	void Move(const FInputActionValue& InputActionValue);
	UFUNCTION()
	void ShiftPressed() {bShiftKeyDown = true;};
	UFUNCTION()
	void ShiftReleased() {bShiftKeyDown = false;};

	bool bShiftKeyDown = false;

	TScriptInterface<IEnemyInterface> LastHoverActor;
	TScriptInterface<IEnemyInterface> CurrentHoverActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;
	
	UAuraAbilitySystemComponent* GetASC();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	/**
	 * Movement
	 */

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	TObjectPtr<USplineComponent> MovementSpline;
};
