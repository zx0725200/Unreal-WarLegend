// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAbility.h"

#include "Character/WarLegendCharacter.h"
#include "Controller/WarLegendPlayerController.h"

AWarLegendCharacter* UHeroAbility::GetHeroCharacterFromActorInfo()
{
	if (!HeroCharacter.IsValid())
	{
		HeroCharacter = Cast<AWarLegendCharacter>(CurrentActorInfo->AvatarActor);
	}
	// .Get()이 알아서 nullptr 반환
	return HeroCharacter.Get();
}

AWarLegendPlayerController* UHeroAbility::GetHeroControllerFromActorInfo()
{
	if (!HeroController.IsValid())
	{
		HeroController = Cast<AWarLegendPlayerController>(CurrentActorInfo->PlayerController);
	}
	// .Get()이 알아서 nullptr 반환
	return HeroController.Get();
}
