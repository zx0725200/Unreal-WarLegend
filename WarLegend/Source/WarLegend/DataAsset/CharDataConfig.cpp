// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/CharDataConfig.h"

#include "Abilities/GameplayAbility.h"
#include "Ability/CharAbilitySystemComponent.h"

void UCharDataConfig::GiveToAbilitySystemComponent(UCharAbilitySystemComponent* InAbilityComponent, const int32 InApplyLevel)
{
	if (!InAbilityComponent)
	{
		return;
	}
	
	GiveAbilities(ActivateOnGivenAbilities, InAbilityComponent, InApplyLevel);
	GiveAbilities(ReactiveAbilities, InAbilityComponent, InApplyLevel); 
}

void UCharDataConfig::GiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities, UCharAbilitySystemComponent* InAbilityComponent, const int32 InApplyLevel)
{
	if (InAbilities.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UGameplayAbility>& Ability : InAbilities)
	{
		if(!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InAbilityComponent->GetAvatarActor();
		AbilitySpec.Level = InApplyLevel;

		InAbilityComponent->GiveAbility(AbilitySpec);
	}
}
