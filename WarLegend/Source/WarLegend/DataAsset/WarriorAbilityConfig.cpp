// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorAbilityConfig.h"
#include "Ability/HeroAbility.h"
#include "GameplayAbilitySpec.h"
#include "Ability/HeroAbilitySystemComponent.h"

bool FWarriorAbilityStruct::IsValid() const
{
	return AbilityTag.IsValid() && WarriorAbility;
}

void UWarriorAbilityConfig::GiveAbilityToComponent(UHeroAbilitySystemComponent* InAbilityComponent)
{
	Super::GiveAbilityToComponent(InAbilityComponent);
	
	for (const FWarriorAbilityStruct& AbilitySet : WarriorAbilityList)
	{
		if(!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.WarriorAbility);
		AbilitySpec.SourceObject = InAbilityComponent->GetAvatarActor();
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.AbilityTag);

		InAbilityComponent->GiveAbility(AbilitySpec);
	}
}
