// Copyright Epic Games, Inc. All Rights Reserved.

#include "WarLegendCharacter.h"

#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Component/BattleInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "DataAsset/BattleInputConfig.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "ETC/Enum.h"
#include "ETC/GamePlayTag.h"

AWarLegendCharacter::AWarLegendCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	BattleCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BattleCameraArm"));
	BattleCameraArm->SetupAttachment(RootComponent);
	
	BattleCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BattleCamera"));
	BattleCamera->SetupAttachment(BattleCameraArm, USpringArmComponent::SocketName);
	
	TopDownCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TopDownCameraArm"));
	TopDownCameraArm->SetupAttachment(RootComponent);
	
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(TopDownCameraArm, USpringArmComponent::SocketName);
	
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	// 데칼 끄기.
	GetMesh()->bReceivesDecals = false;
}

void AWarLegendCharacter::ChangeCamera(const EPlayerLocType InMode)
{
	if (InMode == EPlayerLocType::City)
	{
		SetCityCamera();
	}
	else if (InMode == EPlayerLocType::Battle)
	{
		SetBattleCamera();
	}
}

void AWarLegendCharacter::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);
}

void AWarLegendCharacter::AddControllerYawInput(float Val)
{
	Super::AddControllerYawInput(Val);
}

void AWarLegendCharacter::AddControllerPitchInput(float Val)
{
	Super::AddControllerPitchInput(Val);
}

void AWarLegendCharacter::SetBattleCamera()
{
	BattleCamera->SetActive(true);
	TopDownCamera->SetActive(false);
	
	BattleCameraArm->TargetArmLength = 500.f;
	BattleCameraArm->SocketOffset = FVector(0.0f, 0.0f, 0.0f);
	BattleCameraArm->bUsePawnControlRotation = true;
	
	BattleCamera->bUsePawnControlRotation = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AWarLegendCharacter::SetCityCamera()
{
	BattleCamera->SetActive(false);
	TopDownCamera->SetActive(true);
	
	// Unreal TopDown 기본세팅.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	TopDownCameraArm->SetUsingAbsoluteRotation(true);
	TopDownCameraArm->TargetArmLength = 800.f;
	TopDownCameraArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	TopDownCameraArm->bDoCollisionTest = false;
	
	TopDownCamera->bUsePawnControlRotation = false;
}
