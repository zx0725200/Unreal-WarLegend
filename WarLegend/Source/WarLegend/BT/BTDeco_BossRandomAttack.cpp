// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDeco_BossRandomAttack.h"

UBTDeco_BossRandomAttack::UBTDeco_BossRandomAttack()
{
	NodeName = "Random Attack";
	
	bAllowAbortLowerPri = false;
	bAllowAbortChildNodes = false;
	bAllowAbortNone = true;
}

bool UBTDeco_BossRandomAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return FMath::FRand() < Rate;
}
