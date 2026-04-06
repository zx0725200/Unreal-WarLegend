// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorDataConfig.h"
#include "Ability/WarriorAbility.h"
#include "GameplayAbilitySpec.h"
#include "Ability/CharAbilitySystemComponent.h"

bool FWarriorAbilityStruct::IsValid() const
{
	return AbilityTag.IsValid() && WarriorAbility;
}

void UWarriorDataConfig::GiveToAbilitySystemComponent(UCharAbilitySystemComponent* InAbilityComponent, const int32 InApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InAbilityComponent, InApplyLevel);
	
	for (const FWarriorAbilityStruct& AbilitySet : WarriorAbilityList)
	{
		if(!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.WarriorAbility);
		AbilitySpec.SourceObject = InAbilityComponent->GetAvatarActor();
		AbilitySpec.Level = InApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.AbilityTag);

		InAbilityComponent->GiveAbility(AbilitySpec);
	}
}
