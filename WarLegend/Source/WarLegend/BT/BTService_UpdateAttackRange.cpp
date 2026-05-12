// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTService_UpdateAttackRange::UBTService_UpdateAttackRange()
{
	NodeName = "Update Attack Range";

	Interval = 0.15f;
	RandomDeviation = 0.05f;
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;

	// 디테일 패널에서 어떤 BB 타입의 키만 선택 가능하게 필터링
	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateAttackRange, TargetKey), AActor::StaticClass());
	InRangeKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateAttackRange, InRangeKey));
	RangeKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateAttackRange, RangeKey));
	LastKnownLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_UpdateAttackRange, LastKnownLocationKey));
}

void UBTService_UpdateAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	AAIController* AI = OwnerComp.GetAIOwner();
	APawn* SelfPawn = AI ? AI->GetPawn() : nullptr;
	if (!BlackboardComponent || !SelfPawn) return;

	AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetKey.SelectedKeyName));
	if (!Target) return;
	
	const float Range = (RangeKey.SelectedKeyName != NAME_None)
		? BlackboardComponent->GetValueAsFloat(RangeKey.SelectedKeyName)
		: DefaultRange;
	
	const float DistSq = FVector::DistSquared2D(SelfPawn->GetActorLocation(), Target->GetActorLocation());
	const bool bInRange = DistSq <= FMath::Square(Range);

	BlackboardComponent->SetValueAsBool(InRangeKey.SelectedKeyName, bInRange);
	
	if (AI->GetFocusActor() != Target)
	{
		AI->SetFocus(Target);
	}
}

void UBTService_UpdateAttackRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	// 시작 직후 한번 즉시 갱신 (첫 Interval 만큼 늦게 반응하는 것 방지)
	TickNode(OwnerComp, NodeMemory, 0.f);
}
