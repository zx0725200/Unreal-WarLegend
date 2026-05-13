// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonAbilityConfigBase.h"

#include "Abilities/GameplayAbility.h"
#include "Ability/HeroAbilitySystemComponent.h"
#include "ETC/Define.h"

#include "ETC/Enum.h"

// ? DataConfig 에셋 로드 완료 후 PossessedBy 흐름에서 호출 (Hero: ApplyBattleMode, Enemy: Init 람다)
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

		const UGameplayEffect* EffectCDO = Effect->GetDefaultObject<UGameplayEffect>();	// ? 생성자
		
		// ? 이 Effect는 누가 발동했고 어떤 상황해서 발동했는지 인자로 넘겨줌.
		InAbilityComponent->ApplyGameplayEffectToSelf(EffectCDO, 1, InAbilityComponent->MakeEffectContext());
	}
}

void UCommonAbilityConfigBase::Internal_GiveAbility(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities, UHeroAbilitySystemComponent* InAbilityComponent, EAbilityGiveMode InMode)
{
	for (const TSubclassOf<UGameplayAbility>& Ability : InAbilities)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InAbilityComponent->GetAvatarActor();	// ? Ability가 누구껀지
        
		if (InMode == EAbilityGiveMode::GiveOnly)
		{
			InAbilityComponent->GiveAbility(AbilitySpec);	// ? 부여하고 대기.
		}
		else if (InMode == EAbilityGiveMode::GiveAndActivateOnce)
		{
			InAbilityComponent->GiveAbilityAndActivateOnce(AbilitySpec);	// ? 부여하고 한번 즉시 활성화.
		}
	}
}
