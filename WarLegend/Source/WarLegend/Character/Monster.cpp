// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "ETC/Constant.h"
#include "GameFramework/CharacterMovementComponent.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = false;
 
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	// 회전 값.
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);
	
	// 충돌처리 무시
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
	LapCountWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("LapCountWidget"));
	LapCountWidgetComp->SetupAttachment(GetMesh());
	LapCountWidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	LapCountWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	LapCountWidgetComp->SetDrawSize(FVector2D(100.f, 50.f));
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMonster::AddLapCount()
{
	++LapCount;
	OnLapCountChanged.Broadcast(this, LapCount);
 
	if (LapCount < Constant::MaxLapCount)
		return;
	
	PlayWinSequence();
}

void AMonster::SetMonsterState(const EMonsterState InNewState)
{
	if (CurrentState == InNewState) return;
 
	CurrentState = InNewState;
	
	switch (InNewState)
	{
	case EMonsterState::Patrol:
		if (!RunAnim)
		{
			return;
		}
		
		GetMesh()->PlayAnimation(RunAnim, true);
		break;

	case EMonsterState::Win:
		if (!WinAnim)
		{
			return;
		}
		GetMesh()->PlayAnimation(WinAnim, true);
		break;

	default:
		GetMesh()->Stop();
		break;
	}
}

void AMonster::SetCurrentWaypointIndex(const int32 InIndex)
{
	CurrentWaypointIndex = InIndex;
}

void AMonster::SetPatrolPath(AWLPatrolPathActor* InPatrolPath)
{
	PatrolPath = InPatrolPath;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
	SetMonsterState(EMonsterState::Patrol);
}

void AMonster::PlayWinSequence()
{
	SetMonsterState(EMonsterState::Win);
	GetCharacterMovement()->StopMovementImmediately();
	OnMonsterWin.Broadcast();
}



