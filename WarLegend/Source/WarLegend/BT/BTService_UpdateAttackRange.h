// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UBTService_UpdateAttackRange : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_UpdateAttackRange();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** BB에 등록된 추적 대상 (Object/Actor 타입 키) */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetKey;

	/** 결과를 기록할 Bool 키 */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector InRangeKey;

	/** BB의 Float 키에서 Range를 읽고 싶으면 지정. 비워두면 아래 DefaultRange 사용. */
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector RangeKey;
	
	/** 마지막으로 본 플레이어의 위치*/
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector LastKnownLocationKey;

	/** RangeKey 미지정 시 사용할 고정 사거리 (cm) */
	UPROPERTY(EditAnywhere, Category = "Range", meta = (ClampMin = "0.0"))
	float DefaultRange = 250.f;
	
};
