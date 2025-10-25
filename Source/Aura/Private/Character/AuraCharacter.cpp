// Copyright Kyle Lautenbach 2025


#include "Character/AuraCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAuraCharacter::AAuraCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm =CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;
	PlayerCamera =CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	PlayerCamera->SetupAttachment(SpringArm);

	UCharacterMovementComponent* CharacterMoveComponent = GetCharacterMovement();
	CharacterMoveComponent->bOrientRotationToMovement = true;
	CharacterMoveComponent->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	CharacterMoveComponent->bConstrainToPlane = true;
	CharacterMoveComponent->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}