// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonAbilityConfigBase.h"

#include "Abilities/GameplayAbility.h"
#include "Ability/HeroAbilitySystemComponent.h"
#include "ETC/Define.h"

#include "ETC/Enum.h"

void UCommonAbilityConfigBase::GiveAbilityToComponent(UHeroAbilitySystemComponent* InAbilityComponent)
{
	VALID_RETURN(InAbilityComponent);
    
	Internal_GiveAbility(ActivateOnGivenAbilities, InAbilityComponent, EAbilityGiveMode::GiveAndActivateOnce);
	Internal_GiveAbility(ReactiveAbilities, InAbilityComponent, EAbilityGiveMode::GiveOnly);
	
	if (HeroGamePlayEffects.IsEmpty())
	{
		return;
	}
	
	for (const auto& Effect : HeroGamePlayEffects)
	{
		if (!Effect) continue;

		const UGameplayEffect* EffectCDO = Effect->GetDefaultObject<UGameplayEffect>();
		
		InAbilityComponent->ApplyGameplayEffectToSelf(EffectCDO, 1, InAbilityComponent->MakeEffectContext());
	}
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
