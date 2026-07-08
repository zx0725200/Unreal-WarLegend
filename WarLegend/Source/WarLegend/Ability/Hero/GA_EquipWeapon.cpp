// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_EquipWeapon.h"

#include "EnhancedInputSubsystems.h"
#include "Ability/HeroAbilitySystemComponent.h"
#include "Actor/HeroWeaponBase.h"
#include "AnimInstance/CharacterAnimLayer.h"
#include "ETC/Define.h"

void UGA_EquipWeapon::HandleWeapon(AHeroWeaponBase* InWeapon)
{
	VALID_RETURN(InWeapon);

	const FHeroWeaponData& WeaponData = InWeapon->HeroWeaponData;

	// 1) 무기 전용 Anim으로 변경.
	LinkWeaponAnimLayer(WeaponData.WeaponAnimLayerToLink);

	// 2) 무기 입력 매핑 컨텍스트 추가.
	AddWeaponMappingContext(WeaponData.WeaponInputMappingContext);

	// 3) 무기 기본 어빌리티 부여.
	GrantWeaponAbilities(InWeapon, WeaponData.DefaultWeaponAbilities);
}

void UGA_EquipWeapon::LinkWeaponAnimLayer(const TSubclassOf<UCharacterAnimLayer>& InAnimLayer)
{
	if (!InAnimLayer)
	{
		return;
	}

	if (USkeletalMeshComponent* SkeMesh = GetActorInfo().SkeletalMeshComponent.Get())
	{
		SkeMesh->LinkAnimClassLayers(InAnimLayer);
	}
}

void UGA_EquipWeapon::AddWeaponMappingContext(UInputMappingContext* InMappingContext)
{
	VALID_RETURN(InMappingContext);

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetHeroInputSubsystem();
	VALID_RETURN(InputSubsystem);

	InputSubsystem->AddMappingContext(InMappingContext, 1);
}

void UGA_EquipWeapon::GrantWeaponAbilities(AHeroWeaponBase* InWeapon, const TArray<FHeroAbilitySet>& InAbilitySets)
{
	UHeroAbilitySystemComponent* HeroASC = GetHeroAbilityComponentFromActorInfo();
	VALID_RETURN(HeroASC, InWeapon);

	// 부여 후 반환된 핸들을 무기에 저장(해제 시 제거용).
	TArray<FGameplayAbilitySpecHandle> OutGrantedHandleList;
	HeroASC->GiveWeaponAbilities(InAbilitySets, OutGrantedHandleList);

	InWeapon->SetAbilityHandleList(OutGrantedHandleList);
}
