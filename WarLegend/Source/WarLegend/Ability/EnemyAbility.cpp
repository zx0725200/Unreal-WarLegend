// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAbility.h"

#include "Character/EnemyCharacter.h"

AEnemyCharacter* UEnemyAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid()? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UEnemyAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
