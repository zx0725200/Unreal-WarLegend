// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

class UWidgetComponent;
class AWLPatrolPathActor;

UENUM(BlueprintType)
enum class EMonsterState : uint8
{
	Idle,
	Patrol,
	Win,
	Dead
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMonsterLapCountChanged, AMonster*, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMonsterDead, AMonster*);
DECLARE_MULTICAST_DELEGATE(FOnMonsterWin);

UCLASS()
class WARLEGEND_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	AMonster();
	
	void AddLapCount();
	void SetMonsterState(const EMonsterState InNewState);
	void SetCurrentWaypointIndex(const int32 InIndex);
	void SetPatrolPath(AWLPatrolPathActor* InPatrolPath);
	
	EMonsterState GetMonsterState() const { return CurrentState; }
	int32 GetLapCount() const { return LapCount; }
	int32 GetCurrentWaypointIndex() const { return CurrentWaypointIndex; }
	bool IsWinState() const { return CurrentState == EMonsterState::Win; }
	UWidgetComponent* GetLapCountWidgetComp() const { return LapCountWidgetComp; }
	AWLPatrolPathActor* GetPatrolPath() const { return PatrolPath; }

protected:
	virtual void BeginPlay() override;
	
private:
	void PlayWinSequence();

public:
	FOnMonsterLapCountChanged OnLapCountChanged;
	FOnMonsterDead OnMonsterDead;
	FOnMonsterWin OnMonsterWin;
	
private:
	UPROPERTY()
	TObjectPtr<AWLPatrolPathActor> PatrolPath;
	
	UPROPERTY(VisibleAnywhere, Category = "UI")		// 위젯 가져올때 사용.
	TObjectPtr<UWidgetComponent> LapCountWidgetComp;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimSequenceBase> RunAnim;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TObjectPtr<UAnimSequenceBase> WinAnim;
	
	int32 LapCount = 0;									// 몬스터가 가지고있는 바퀴 수
	int32 CurrentWaypointIndex = 0;						// 현재 몬스터가 지나고 있는 체크포인트
	EMonsterState CurrentState = EMonsterState::Idle;
};
