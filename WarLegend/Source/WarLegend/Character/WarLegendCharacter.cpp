#include "WarLegendCharacter.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Ability/CharAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "ETC/Constant.h"
#include "ETC/Enum.h"

AWarLegendCharacter::AWarLegendCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	BattleCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BattleCameraArm"));
	BattleCameraArm->SetupAttachment(RootComponent);
	BattleCameraArm->TargetArmLength = Constant::BattleArmLength;
	BattleCameraArm->bUsePawnControlRotation = true;
	
	BattleCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BattleCamera"));
	BattleCamera->SetupAttachment(BattleCameraArm, USpringArmComponent::SocketName);
	BattleCamera->bUsePawnControlRotation = false;
	
	TopDownCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TopDownCameraArm"));
	TopDownCameraArm->SetupAttachment(RootComponent);
	TopDownCameraArm->SetUsingAbsoluteRotation(true);
	TopDownCameraArm->TargetArmLength = Constant::TopDownArmLength;
	TopDownCameraArm->SetRelativeRotation(Constant::TopDownArmRotation);
	TopDownCameraArm->bDoCollisionTest = false;
	
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(TopDownCameraArm, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;
	
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
		ApplyCityMovement();
	}
	else if (InMode == EPlayerLocType::Battle)
	{
		SetBattleCamera();
		ApplyBattleMovement();
	}
}

UAbilitySystemComponent* AWarLegendCharacter::GetAbilitySystemComponent() const
{
	return CharAbilitySystemComponent;
}

void AWarLegendCharacter::SetBattleCamera()
{
	BattleCamera->SetActive(true);
	TopDownCamera->SetActive(false);
}

void AWarLegendCharacter::SetCityCamera()
{
	BattleCamera->SetActive(false);
	TopDownCamera->SetActive(true);
}

void AWarLegendCharacter::ApplyCityMovement()
{
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->bOrientRotationToMovement = true;
	MoveComp->RotationRate = FRotator(0.f, Constant::CityRotationYawRate, 0.f);
	MoveComp->bConstrainToPlane = true;
	MoveComp->bSnapToPlaneAtStart = true;
}

void AWarLegendCharacter::ApplyBattleMovement()
{
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->bOrientRotationToMovement = true;
	MoveComp->RotationRate = FRotator(0.f, Constant::BattleRotationYawRate, 0.f);
	MoveComp->MaxWalkSpeed = Constant::BattleMaxWalkSpeed;
	MoveComp->BrakingDecelerationWalking = Constant::BattleBrakingDeceleration;
}
