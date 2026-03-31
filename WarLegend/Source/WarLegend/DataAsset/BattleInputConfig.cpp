// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleInputConfig.h"

UInputAction* UBattleInputConfig::GetBattleInputAction(const FGameplayTag& InInputTag)
{
	for (const auto& BattleInputConfig : BattleInputActions)
	{
		if (BattleInputConfig.BattleTag == InInputTag && BattleInputConfig.BattleAction)
		{
			return BattleInputConfig.BattleAction;
		}
	}
	
	return nullptr;
}
