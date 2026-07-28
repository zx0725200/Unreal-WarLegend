#include "WarLegendCharacter.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShakeBase.h"
#include "DataManager/DungeonManager.h"
#include "Engine/GameInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "Ability/HeroAbilitySystemComponent.h"
#include "Component/HeroCombatComponent.h"
#include "Component/LockOnComponent.h"
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
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

AWarLegendCharacter::AWarLegendCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// ? 회전 불가능하게.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	BattleCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("BattleCameraArm"));
	BattleCameraArm->SetupAttachment(RootComponent);
	BattleCameraArm->TargetArmLength = Constant::BattleArmLength;
	BattleCameraArm->bUsePawnControlRotation = true;	// ? 입력 따라 회전
	BattleCameraArm->bEnableCameraLag = true;			// ? 카메라가 부드럽게 따라오도록.
	BattleCameraArm->CameraLagMaxTimeStep = 0.005f;
	BattleCameraArm->bDoCollisionTest = false;			// ? 보스 등과 겹쳐도 카메라가 당겨지지(줌) 않게
	
	BattleCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BattleCamera"));
	BattleCamera->SetupAttachment(BattleCameraArm, USpringArmComponent::SocketName);
	BattleCamera->bUsePawnControlRotation = false;
	
	TopDownCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TopDownCameraArm"));
	TopDownCameraArm->SetupAttachment(RootComponent);
	TopDownCameraArm->SetUsingAbsoluteRotation(true);
	TopDownCameraArm->TargetArmLength = Constant::TopDownArmLength;
	TopDownCameraArm->SetRelativeRotation(Constant::TopDownArmRotation);
	TopDownCameraArm->bDoCollisionTest = false;			// ? 벽이랑 부딪혀도 줌 안하게 
	
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(TopDownCameraArm, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;
	
	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));

	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));
	
	// ? AI가 이 액터를 감지 할 수 있게 만들어주는 Component
	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("StimuliSource");
	StimuliSource->bAutoRegister = true;
	StimuliSource->RegisterForSense(UAISense_Sight::StaticClass());	// ? 보스가 플레이어를 볼수있게 시야 설정.
}

void AWarLegendCharacter::ChangeCamera(const EPlayerLocType InMode)
{
	LoadBattleMode();
	
	// if (InMode == EPlayerLocType::City)
	// {
	// 	SetCityCamera();
	// 	ApplyCityMovement();
	// }
	// else if (InMode == EPlayerLocType::Battle)
	// {
	// 	LoadBattleMode();
	// }
}

UHeroCombatComponent* AWarLegendCharacter::GetHeroCombatComponent()
{
	return HeroCombatComponent;
}

void AWarLegendCharacter::ToggleLockOn()
{
	if (LockOnComponent)
	{
		LockOnComponent->ToggleLockOn();
	}
}

bool AWarLegendCharacter::IsLockedOn() const
{
	return LockOnComponent && LockOnComponent->IsLockedOn();
}

void AWarLegendCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AWarLegendCharacter::BeginDungeonEntry()
{
	bDungeonEntrySequence = true;

	// 상공에 텔레포트된 직후이므로 즉시 낙하 상태로 전환.
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->SetMovementMode(MOVE_Falling);
	}
}

void AWarLegendCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	// 일반 점프 착지에는 반응하지 않고, 던전 입장 낙하의 첫 착지에만 연출을 재생한다.
	if (!bDungeonEntrySequence)
	{
		return;
	}
	bDungeonEntrySequence = false;

	// 착지 이펙트(발밑).
	if (LandingEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, LandingEffect, GetActorLocation(), FRotator::ZeroRotator);
	}

	// 착지 카메라 쉐이크.
	if (LandingCameraShake)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			PC->ClientStartCameraShake(LandingCameraShake);
		}
	}

	// 던전 매니저에 착지 알림 → 입력 복구 + 보스전 시작.
	if (const UWorld* World = GetWorld())
	{
		if (UGameInstance* GI = World->GetGameInstance())
		{
			if (UDungeonManager* DungeonMgr = GI->GetSubsystem<UDungeonManager>())
			{
				DungeonMgr->OnPlayerEntryLanded();
			}
		}
	}
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

UPawnCombatComponentBase* AWarLegendCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

void AWarLegendCharacter::LoadBattleMode()
{
	if (DataConfig.IsNull())
	{
		return;
	}
	
	if (DataConfig.Get())
	{
		ApplyBattleMode();
		return;
	}
	
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	DataLoadHandle = Streamable.RequestAsyncLoad(DataConfig.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AWarLegendCharacter::ApplyBattleMode));
}

// ? LoadBattleMode에서 RequestAsyncLoad 완료 콜백으로 호출됨
void AWarLegendCharacter::ApplyBattleMode()
{
	UCommonAbilityConfigBase* LoadedData = DataConfig.Get();
	VALID_RETURN(LoadedData, HeroAbilitySystemComponent);

	LoadedData->GiveAbilityToComponent(HeroAbilitySystemComponent);
	
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
	MoveComp->bOrientRotationToMovement = true;	// ? 캐릭터가 이동방향으로 자동 회전
	MoveComp->RotationRate = FRotator(0.f, Constant::CityRotationYawRate, 0.f);
	MoveComp->bConstrainToPlane = true;			// ? z축 이동 제한
	MoveComp->bSnapToPlaneAtStart = true;		// ? 스폰 될때 자동으로 지형에 붙기
}

void AWarLegendCharacter::ApplyBattleMovement()
{
	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->bOrientRotationToMovement = true;
	MoveComp->RotationRate = FRotator(0.f, Constant::BattleRotationYawRate, 0.f);
	MoveComp->MaxWalkSpeed = Constant::BattleMaxWalkSpeed;
	MoveComp->BrakingDecelerationWalking = Constant::BattleBrakingDeceleration;	// ? 이동 입력을 멈췄을때 정지 하는 마찰력 느낌. 클수록 빠르게 멈춤.
}
