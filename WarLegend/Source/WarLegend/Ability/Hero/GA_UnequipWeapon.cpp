// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_UnequipWeapon.h"

#include "EnhancedInputSubsystems.h"
#include "Ability/HeroAbilitySystemComponent.h"
#include "Actor/HeroWeaponBase.h"
#include "AnimInstance/CharacterAnimLayer.h"
#include "ETC/Define.h"

void UGA_UnequipWeapon::HandleWeapon(AHeroWeaponBase* InWeapon)
{
	VALID_RETURN(InWeapon);

	const FHeroWeaponData& WeaponData = InWeapon->HeroWeaponData;

	// 1) 무기 Anim 링크 해제.
	UnlinkWeaponAnimLayer(WeaponData.WeaponAnimLayerToLink);

	// 2) 무기 입력 매핑 컨텍스트 제거.
	RemoveWeaponMappingContext(WeaponData.WeaponInputMappingContext);

	// 3) 무기 어빌리티 제거.
	RemoveWeaponAbilities(InWeapon);
}

void UGA_UnequipWeapon::UnlinkWeaponAnimLayer(const TSubclassOf<UCharacterAnimLayer>& InAnimLayer)
{
	if (!InAnimLayer)
	{
		return;
	}

	if (USkeletalMeshComponent* SkeMesh = GetActorInfo().SkeletalMeshComponent.Get())
	{
		SkeMesh->UnlinkAnimClassLayers(InAnimLayer);
	}
}

void UGA_UnequipWeapon::RemoveWeaponMappingContext(UInputMappingContext* InMappingContext)
{
	VALID_RETURN(InMappingContext);

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetHeroInputSubsystem();
	VALID_RETURN(InputSubsystem);

	InputSubsystem->RemoveMappingContext(InMappingContext);
}

void UGA_UnequipWeapon::RemoveWeaponAbilities(AHeroWeaponBase* InWeapon)
{
	UHeroAbilitySystemComponent* HeroASC = GetHeroAbilityComponentFromActorInfo();
	VALID_RETURN(HeroASC, InWeapon);
	
	TArray<FGameplayAbilitySpecHandle> HandleListToRemove = InWeapon->GetAbilityHandleList();
	HeroASC->RemoveWeaponAbilities(HandleListToRemove);

	// 무기 쪽 핸들 목록도 비워 상태를 일치시킨다.
	InWeapon->SetAbilityHandleList(TArray<FGameplayAbilitySpecHandle>());
}
