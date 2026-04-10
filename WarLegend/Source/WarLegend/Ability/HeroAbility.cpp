// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAbility.h"

#include "Character/WarLegendCharacter.h"
#include "Controller/WarLegendPlayerController.h"

AWarLegendCharacter* UHeroAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedWarriorHeroCharacter.IsValid())
	{
		CachedWarriorHeroCharacter = Cast<AWarLegendCharacter>(CurrentActorInfo->AvatarActor);
	}
	// .Get()이 알아서 nullptr 반환
	return CachedWarriorHeroCharacter.Get();
}

AWarLegendPlayerController* UHeroAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedWarriorHeroController.IsValid())
	{
		CachedWarriorHeroController = Cast<AWarLegendPlayerController>(CurrentActorInfo->PlayerController);
	}
	// .Get()이 알아서 nullptr 반환
	return CachedWarriorHeroController.Get();
}
