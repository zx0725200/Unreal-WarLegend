// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorAbility.h"

#include "Character/WarLegendCharacter.h"
#include "Controller/WarLegendPlayerController.h"

AWarLegendCharacter* UWarriorAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedWarriorHeroCharacter.IsValid())
	{
		CachedWarriorHeroCharacter = Cast<AWarLegendCharacter>(CurrentActorInfo->AvatarActor);
	}
   
	return CachedWarriorHeroCharacter.IsValid()? CachedWarriorHeroCharacter.Get() : nullptr;
}

AWarLegendPlayerController* UWarriorAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedWarriorHeroController.IsValid())
	{
		CachedWarriorHeroController = Cast<AWarLegendPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedWarriorHeroController.IsValid()? CachedWarriorHeroController.Get() : nullptr;
}

UCharCombatComponent* UWarriorAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetCharCombatComponent();
}
