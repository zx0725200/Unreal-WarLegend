// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"

#include "Actor/WLPatrolPathActor.h"
#include "Character/Monster.h"
#include "ETC/Constant.h"
#include "Navigation/PathFollowingComponent.h"


AMonsterAIController::AMonsterAIController()
{
	bSetControlRotationFromPawnOrientation = false;
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	CachedMonster = Cast<AMonster>(InPawn);
	if (!CachedMonster)
	{
		return;
	}
	
	CachedPatrolPath = CachedMonster->GetPatrolPath();
	if (!CachedPatrolPath) 
	{
		return;
	}
	
	MoveToNextWaypoint();
}

void AMonsterAIController::OnUnPossess()
{
	CachedMonster = nullptr;
	CachedPatrolPath = nullptr;
	
	Super::OnUnPossess();
}

void AMonsterAIController::MoveToNextWaypoint()
{
	if (!CachedMonster || !CachedPatrolPath) 
	{
		return;
	}
	
	if (CachedMonster->IsWinState() || CachedMonster->GetMonsterState() == EMonsterState::Dead) 
	{
		return;
	}
	
	const int32 WayPointIndex = CachedMonster->GetCurrentWaypointIndex();
	FVector Target = CachedPatrolPath->GetWaypointWorldLocation(WayPointIndex);
	Target.Z = CachedMonster->GetActorLocation().Z;  // Z는 몬스터 현재 높이로
	
	SetFocalPoint(Target);	// 이동 방향으로 바라보게
	
	FAIMoveRequest MoveReq;
	MoveReq.SetGoalLocation(Target);
	MoveReq.SetAcceptanceRadius(Constant::MonsterAcceptRange);
	MoveReq.SetUsePathfinding(true);

	MoveTo(MoveReq);
}

void AMonsterAIController::OnMoveCompleted(const FAIRequestID RequestID, const EPathFollowingResult::Type Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	
	if (!CachedMonster || !CachedPatrolPath) 
	{
		return;
	}
	
	if (CachedMonster->IsWinState() || CachedMonster->GetMonsterState() == EMonsterState::Dead) 
	{
		return;
	}
 
	if (Result != EPathFollowingResult::Success)
	{
		FTimerHandle RetryTimer;
		GetWorld()->GetTimerManager().SetTimer(RetryTimer, this, &AMonsterAIController::MoveToNextWaypoint, 1.0f, false);
		return;
	}
 
	const int32 WaypointCount = CachedPatrolPath->GetWaypointCount();
	const int32 CurrentIndex = CachedMonster->GetCurrentWaypointIndex();
	const int32 NextIndex = (CurrentIndex + 1) % WaypointCount;
 
	if (NextIndex == 0)
	{
		CachedMonster->AddLapCount();
		if (CachedMonster->IsWinState()) 
		{
			return;
		}
	}
 
	CachedMonster->SetCurrentWaypointIndex(NextIndex);
	MoveToNextWaypoint();
}

