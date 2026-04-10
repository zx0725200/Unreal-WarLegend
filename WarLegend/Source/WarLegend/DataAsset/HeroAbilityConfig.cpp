#include "HeroAbilityConfig.h"
#include "Ability/HeroAbility.h"
#include "GameplayAbilitySpec.h"
#include "Ability/HeroAbilitySystemComponent.h"
#include "ETC/Struct.h"

void UHeroAbilityConfig::GiveAbilityToComponent(UHeroAbilitySystemComponent* InAbilityComponent)
{
	Super::GiveAbilityToComponent(InAbilityComponent);
	
	for (const FHeroAbilitySet& AbilitySet : WarriorAbilityList)
	{
		if(!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InAbilityComponent->GetAvatarActor();
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.BattleTag);

		InAbilityComponent->GiveAbility(AbilitySpec);
	}
}
