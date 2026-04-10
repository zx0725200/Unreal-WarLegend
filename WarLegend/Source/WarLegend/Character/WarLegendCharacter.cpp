#include "WarLegendCharacter.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Ability/HeroAbilitySystemComponent.h"
#include "Component/HeroCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "DataAsset/CommonAbilityConfigBase.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
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
	
	CharCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("CharCombatComponent"));
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
		LoadBattleMode();
	}
}

UHeroCombatComponent* AWarLegendCharacter::GetCharCombatComponent()
{
	return CharCombatComponent;
}

void AWarLegendCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AWarLegendCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (DataLoadHandle.IsValid())
	{
		DataLoadHandle->CancelHandle();
		DataLoadHandle.Reset();
	}
	
	Super::EndPlay(EndPlayReason);
}

void AWarLegendCharacter::LoadBattleMode()
{
	if (CharDataConfig.IsNull())
	{
		return;
	}
	
	if (CharDataConfig.Get())
	{
		ApplyBattleMode();
		return;
	}
	
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	DataLoadHandle = Streamable.RequestAsyncLoad(CharDataConfig.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AWarLegendCharacter::ApplyBattleMode));
}

void AWarLegendCharacter::ApplyBattleMode()
{
	UCommonAbilityConfigBase* LoadedData = CharDataConfig.Get();
	if (!LoadedData || !CharAbilitySystemComponent)
	{
		return;
	}

	LoadedData->GiveAbilityToComponent(CharAbilitySystemComponent);
	
	SetBattleCamera();
	ApplyBattleMovement();
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
