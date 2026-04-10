// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonAbilityConfigBase.h"

#include "Abilities/GameplayAbility.h"
#include "Ability/HeroAbilitySystemComponent.h"

#include "ETC/Enum.h"

void UCommonAbilityConfigBase::GiveAbilityToComponent(UHeroAbilitySystemComponent* InAbilityComponent)
{
	if (!InAbilityComponent) return;
    
	Internal_GiveAbility(ActivateOnGivenAbilities, InAbilityComponent, EAbilityGiveMode::GiveAndActivateOnce);
	Internal_GiveAbility(ReactiveAbilities, InAbilityComponent, EAbilityGiveMode::GiveOnly);
}

void UCommonAbilityConfigBase::Internal_GiveAbility(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities, UHeroAbilitySystemComponent* InAbilityComponent, EAbilityGiveMode InMode)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : InAbilities)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InAbilityComponent->GetAvatarActor();
        
		if (InMode == EAbilityGiveMode::GiveOnly)
		{
			InAbilityComponent->GiveAbility(AbilitySpec);
		}
		else if (InMode == EAbilityGiveMode::GiveAndActivateOnce)
		{
			InAbilityComponent->GiveAbilityAndActivateOnce(AbilitySpec);
		}
	}
}
