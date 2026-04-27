// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "HeroAbilitySystemComponent.h"
#include "Character/WarLegendCharacter.h"
#include "Controller/WarLegendPlayerController.h"
#include "ETC/Enum.h"
#include "ETC/GamePlayTag.h"

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

FGameplayEffectSpecHandle UHeroAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> InEffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount)
{
	check(InEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetHeroAbilityComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(),GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetHeroAbilityComponentFromActorInfo()->MakeOutgoingSpec(
		InEffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		GamePlayTag::Shared_Event_BaseDamage,
		InWeaponBaseDamage
	);

	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag,InCurrentComboCount);
	}

	return EffectSpecHandle;
}

FActiveGameplayEffectHandle UHeroAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());

	return GetHeroAbilityComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC
	);
}

FActiveGameplayEffectHandle UHeroAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle, EConfirmType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor,InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied()? EConfirmType::Successful : EConfirmType::Failed;

	return ActiveGameplayEffectHandle;
}
