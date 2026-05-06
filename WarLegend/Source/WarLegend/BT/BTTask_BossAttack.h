// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossAttack.generated.h"

struct FAbilityEndedData;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WARLEGEND_API UBTTask_BossAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_BossAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** 활성화할 어빌리티의 태그. 예: Ability.Boss.MeleeAttack */
	UPROPERTY(EditAnywhere, Category = "Ability")
	FGameplayTagContainer AbilityTagsToActivate;

private:
	void OnAbilityEndedCallback(const FAbilityEndedData& EndedData);
	void CleanupBindings();

	UPROPERTY()
	TWeakObjectPtr<UBehaviorTreeComponent> CachedOwnerComp;

	UPROPERTY()
	TWeakObjectPtr<UAbilitySystemComponent> CachedASC;

	FDelegateHandle OnAbilityEndedHandle;
};
