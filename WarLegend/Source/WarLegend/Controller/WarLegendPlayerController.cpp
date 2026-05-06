#include "WarLegendPlayerController.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "UIManager.h"
#include "UIManagerImpl.h"
#include "Ability/HeroAbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "Character/WarLegendCharacter.h"
#include "Component/BattleInputComponent.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "ETC/GamePlayTag.h"

AWarLegendPlayerController::AWarLegendPlayerController()
{
	bIsTouch = false;
	bMoveToMouseCursor = false;

	// create the path following comp
	PathFollowingComponent = CreateDefaultSubobject<UPathFollowingComponent>(TEXT("Path Following Component"));

	// configure the controller
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AWarLegendPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (!IsLocalPlayerController())
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	VALID_RETURN(Subsystem);
	
	UBattleInputComponent* BattleInput = Cast<UBattleInputComponent>(InputComponent);
	VALID_RETURN(BattleInput);
	VALID_RETURN(DefaultMappingContext, InputBattleDataAsset, SetDestinationClickAction, SetInventoryAction, SetEscClickAction);
	
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	
	// Battle용 바인딩
	BattleInput->BindNativeInputAction(InputBattleDataAsset, GamePlayTag::Battle_Move, ETriggerEvent::Triggered, this, &AWarLegendPlayerController::OnBattleMove);
	BattleInput->BindNativeInputAction(InputBattleDataAsset, GamePlayTag::Battle_Look, ETriggerEvent::Triggered, this, &AWarLegendPlayerController::OnBattleLook);
	
	BattleInput->BindAbilityInputAction(InputBattleDataAsset, this, &ThisClass::OnAbilityInputPressed, &ThisClass::OnAbilityInputReleased);

	// City/공통 바인딩
	BattleInput->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AWarLegendPlayerController::OnInputStarted);
	BattleInput->BindAction(SetInventoryAction, ETriggerEvent::Started, this, &AWarLegendPlayerController::OnInventoryOpen);
	BattleInput->BindAction(SetEscClickAction, ETriggerEvent::Started, this, &AWarLegendPlayerController::OnEscClicked);
}

void AWarLegendPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	Init();
}

void AWarLegendPlayerController::OnInputStarted()
{
	StopMovement();

	if (!IsUpdateCachedDestination())
	{
		return;
	}
	
	MoveOnceToCachedDestination();
}

void AWarLegendPlayerController::OnInventoryOpen()
{
	UUIManagerImpl* UIMgr = GTGetMgrImpl(UIManager);
	VALID_RETURN(UIMgr);
	
	UIMgr->ShowUI(TEXT("ScreenInventory"));
}

void AWarLegendPlayerController::OnEscClicked()
{
	UUIManagerImpl* UIMgr = GTGetMgrImpl(UIManager);
	VALID_RETURN(UIMgr);
	
	UIMgr->HandleEscClick();
}

void AWarLegendPlayerController::OnBattleMove(const FInputActionValue& InActionValue)
{
	AWarLegendCharacter* MyCharacter = Cast<AWarLegendCharacter>(GetPawn());
	VALID_RETURN(MyCharacter);
	
	const FVector2D MoveVector = InActionValue.Get<FVector2D>();
	const FRotator MoveRotation(0.f, GetControlRotation().Yaw, 0.f);
	
	if (MoveVector.Y != 0.f)
	{
		const FVector ForwardDir = MoveRotation.RotateVector(FVector::ForwardVector);
		
		MyCharacter->AddMovementInput(ForwardDir, MoveVector.Y);
	}
	
	if (MoveVector.X != 0.f)
	{
		const FVector RightDir = MoveRotation.RotateVector(FVector::RightVector);
		
		MyCharacter->AddMovementInput(RightDir, MoveVector.X);
	}
}

void AWarLegendPlayerController::OnBattleLook(const FInputActionValue& InActionValue)
{
	AWarLegendCharacter* MyCharacter = Cast<AWarLegendCharacter>(GetPawn());
	VALID_RETURN(MyCharacter);
	
	const FVector2D MoveVector = InActionValue.Get<FVector2D>();
	if (MoveVector.X != 0.f)
	{
		MyCharacter->AddControllerYawInput(MoveVector.X);
	}
}

void AWarLegendPlayerController::OnAbilityInputPressed(const FGameplayTag InTag)
{
	AWarLegendCharacter* MyCharacter = Cast<AWarLegendCharacter>(GetPawn());
	VALID_RETURN(MyCharacter);
	
	MyCharacter->GetHeroAbilitySystemComponent()->OnAbilityInputPressed(InTag);
}

void AWarLegendPlayerController::OnAbilityInputReleased(FGameplayTag InTag)
{
}

void AWarLegendPlayerController::MoveOnceToCachedDestination()
{
	MoveToClickOrCloset(CachedDestination);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

bool AWarLegendPlayerController::IsUpdateCachedDestination()
{
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	
	// If we hit a surface, cache the location
	if (bHitSuccessful && Hit.bBlockingHit)
	{
		CachedDestination = Hit.Location;
		return true;
	}
	
	return false;
}

// BeginPlay에서 호출 - SetupInputComponent가 먼저 끝난 뒤 진입, 카메라/타이틀 초기화 담당
void AWarLegendPlayerController::Init()
{
	ChangeBattle();
	SetMouseState();
	ShowTitle();
}

void AWarLegendPlayerController::ShowTitle() const
{
	UUIManagerImpl* UIMgr = GTGetMgrImpl(UIManager);
	VALID_RETURN(UIMgr);
	
	UIMgr->ShowUI(TEXT("ScreenTitle"));
}

void AWarLegendPlayerController::SetMouseState()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;

	// 캡처 설정
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		LocalPlayer->ViewportClient->SetMouseCaptureMode(EMouseCaptureMode::NoCapture);
	}
}

void AWarLegendPlayerController::ChangeCity()
{
	VALID_RETURN(DefaultMappingContext, InputBattleDataAsset->MappingContext);
	
	AWarLegendCharacter* MyCharacter = Cast<AWarLegendCharacter>(GetPawn());
	VALID_RETURN(MyCharacter);
	
	auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	VALID_RETURN(Subsystem);
	
	Subsystem->RemoveMappingContext(InputBattleDataAsset->MappingContext);
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	MyCharacter->ChangeCamera(EPlayerLocType::City);
}

void AWarLegendPlayerController::ChangeBattle()
{
	VALID_RETURN(DefaultMappingContext, InputBattleDataAsset->MappingContext);
	
	AWarLegendCharacter* MyCharacter = Cast<AWarLegendCharacter>(GetPawn());
	VALID_RETURN(MyCharacter);
	
	auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	VALID_RETURN(Subsystem);
	
	Subsystem->RemoveMappingContext(DefaultMappingContext);
	Subsystem->AddMappingContext(InputBattleDataAsset->MappingContext, 0);
	MyCharacter->ChangeCamera(EPlayerLocType::Battle);
}

void AWarLegendPlayerController::ChangeLocation(const FVector& InVector)
{
	AWarLegendCharacter* MyCharacter = Cast<AWarLegendCharacter>(GetPawn());
	VALID_RETURN(MyCharacter);
	
	MyCharacter->SetActorLocation(InVector);
}

void AWarLegendPlayerController::MoveToClickOrCloset(const FVector& InClickLocation)
{
	FVector Location;
	if (IsReachableLocation(InClickLocation, Location))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Location);
	}
}

bool AWarLegendPlayerController::IsReachableLocation(const FVector& InClickLocation, FVector& OutLocation) const
{
	APawn* MyPawn = GetPawn();
	if (!MyPawn) return false;

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSystem) return false;

	// 클릭 지점을 네비메시 위로 투영 (오프 네비 클릭 방지)
	FNavLocation OutNavLoc;
	const FVector Extent(200.f, 200.f, 500.f); // 상황 따라 조절
	if (!NavSystem->ProjectPointToNavigation(InClickLocation, OutNavLoc, Extent))
	{
		return false;
	}

	const FVector Start = MyPawn->GetActorLocation();
	const FVector Goal  = OutNavLoc.Location;

	// 경로 생성 (부분 경로면 마지막 도달 점 사용)
	UNavigationPath* Path = NavSystem->FindPathToLocationSynchronously(GetWorld(), Start, Goal, MyPawn);

	if (!Path || Path->PathPoints.Num() == 0)
	{
		// 경로를 못 만들면 그냥 투영점으로라도 시도
		OutLocation = Goal;
		return true;
	}

	// Partial이면 “갈 수 있는 데까지” = 마지막 PathPoint
	OutLocation = Path->PathPoints.Last();
	return true;
}
