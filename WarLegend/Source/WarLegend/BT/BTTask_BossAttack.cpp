// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossAttack.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"

UBTTask_BossAttack::UBTTask_BossAttack()
{
	NodeName = "Boss Attack";

	// ? 멤버 변수(CachedASC, OnAbilityEndedHandle 등)를 사용하므로
	// ? 인스턴스화 필수. 안 켜면 BT 노드가 공유 상태가 돼서 보스 여러 마리일 때 박살남.
	bCreateNodeInstance = true;

	bNotifyTick = false;
}

EBTNodeResult::Type UBTTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AI = OwnerComp.GetAIOwner();
	APawn* Pawn = AI ? AI->GetPawn() : nullptr;
	if (!Pawn) return EBTNodeResult::Failed;

	IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Pawn);
	UAbilitySystemComponent* ASC = ASI ? ASI->GetAbilitySystemComponent() : nullptr;
	if (!ASC) return EBTNodeResult::Failed;

	if (AbilityTagsToActivate.IsEmpty()) return EBTNodeResult::Failed;

	const bool bActivated = ASC->TryActivateAbilitiesByTag(AbilityTagsToActivate);
	if (!bActivated)
	{
		// 쿨타임/코스트 부족/조건 불충족 등으로 활성화 실패
		return EBTNodeResult::Failed;
	}

	// 캐싱 + 종료 콜백 바인딩
	CachedOwnerComp = &OwnerComp;
	CachedASC = ASC;
	OnAbilityEndedHandle = ASC->OnAbilityEnded.AddUObject(this, &UBTTask_BossAttack::OnAbilityEndedCallback);

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_BossAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// BT가 이 Task를 Abort 시키면(타겟 잃음, 거리 벗어남 등) 어빌리티도 취소
	if (CachedASC.IsValid())
	{
		FGameplayTagContainer EmptyTags;
		CachedASC->CancelAbilities(&AbilityTagsToActivate, &EmptyTags);
	}
	CleanupBindings();
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UBTTask_BossAttack::OnAbilityEndedCallback(const FAbilityEndedData& EndedData)
{
	if (!EndedData.AbilityThatEnded) return;

	// ASC->OnAbilityEnded는 모든 어빌리티 종료에 호출되니
	// 이게 정말 "내가 활성화한" 어빌리티 종료인지 태그로 필터링
	if (!EndedData.AbilityThatEnded->AbilityTags.HasAny(AbilityTagsToActivate))
	{
		return;
	}

	UBehaviorTreeComponent* Owner = CachedOwnerComp.Get();
	const bool bCancelled = EndedData.bWasCancelled;

	CleanupBindings();

	if (Owner)
	{
		FinishLatentTask(*Owner, bCancelled ? EBTNodeResult::Failed : EBTNodeResult::Succeeded);
	}
}

void UBTTask_BossAttack::CleanupBindings()
{
	if (CachedASC.IsValid() && OnAbilityEndedHandle.IsValid())
	{
		CachedASC->OnAbilityEnded.Remove(OnAbilityEndedHandle);
	}
	
	OnAbilityEndedHandle.Reset();
	CachedASC.Reset();
	CachedOwnerComp.Reset();
}
