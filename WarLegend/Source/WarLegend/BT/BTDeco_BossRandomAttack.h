// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDeco_BossRandomAttack.generated.h"

/**
 * 
 */
UCLASS()
class WARLEGEND_API UBTDeco_BossRandomAttack : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDeco_BossRandomAttack();
	
protected:
	UPROPERTY(EditAnywhere, Category="Random", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Rate = 0.5f;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
