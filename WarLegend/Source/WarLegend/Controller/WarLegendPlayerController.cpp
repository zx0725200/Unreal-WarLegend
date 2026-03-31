#include "WarLegendPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Engine/LocalPlayer.h"
#include "WarLegend.h"
#include "Character/WarLegendCharacter.h"
#include "ETC/Define.h"
#include "ETC/Enum.h"
#include "Presenter/UIFlowPresenter.h"

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
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Only set up input on local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			// Setup mouse input events
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AWarLegendPlayerController::OnInputStarted);
			EnhancedInputComponent->BindAction(SetInventoryAction, ETriggerEvent::Started, this, &AWarLegendPlayerController::OnInventoryOpen);
			EnhancedInputComponent->BindAction(SetEscClickAction, ETriggerEvent::Started, this, &AWarLegendPlayerController::OnEscClicked);
			
			// Setup touch input events
			EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AWarLegendPlayerController::OnInputStarted);
		}
		else
		{
			UE_LOG(LogWarLegend, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}
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
	const auto UIPresenter = GTGetMgr(UUIFlowPresenter);
	if (!UIPresenter)
	{
		return;
	}
	
	UIPresenter->OpenScreenInventory();
}

void AWarLegendPlayerController::OnEscClicked()
{
	const auto UIPresenter = GTGetMgr(UUIFlowPresenter);
	if (!UIPresenter)
	{
		return;
	}
	
	UIPresenter->HandleEscClick();
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

void AWarLegendPlayerController::Init()
{
	ChangeCityCamera();
	SetMouseState();
	ShowTitle();
}

void AWarLegendPlayerController::ShowTitle() const
{
	const auto UIPresenter = GTGetMgr(UUIFlowPresenter);
	if (!UIPresenter)
	{
		return;
	}
	
	UIPresenter->OpenScreenTitle();
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

void AWarLegendPlayerController::ChangeCityCamera()
{
	AWarLegendCharacter* MyCharacter = Cast<AWarLegendCharacter>(GetPawn());
	if (!MyCharacter)
	{
		return;
	}
	
	MyCharacter->ChangeCamera(ECameraMode::City);
}

void AWarLegendPlayerController::ChangeBattleCamera()
{
	AWarLegendCharacter* MyCharacter = Cast<AWarLegendCharacter>(GetPawn());
	if (!MyCharacter)
	{
		return;
	}
	
	MyCharacter->ChangeCamera(ECameraMode::Battle);
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
