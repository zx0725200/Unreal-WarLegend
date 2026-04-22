// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAbilityConfig.h"

#include "Ability/EnemyAbility.h"
#include "Ability/HeroAbilitySystemComponent.h"

void UEnemyAbilityConfig::GiveAbilityToComponent(UHeroAbilitySystemComponent* InAbilityComponent)
{
	Super::GiveAbilityToComponent(InAbilityComponent);
	
	for (const auto& AbilitySet : EnemyAbilityList)
	{
		if(!AbilitySet) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet);
		AbilitySpec.SourceObject = InAbilityComponent->GetAvatarActor();
		
		InAbilityComponent->GiveAbility(AbilitySpec);
	}
}
