// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GA_WeaponEquipBase.h"
#include "GA_EquipWeapon.generated.h"

struct FHeroAbilitySet;
class AHeroWeaponBase;
class UInputMappingContext;
class UCharacterAnimLayer;
/**
 * 무기 장착: AnimLayer 링크 / 입력 매핑 컨텍스트 추가 / 무기 어빌리티 부여.
 */
UCLASS()
class WARLEGEND_API UGA_EquipWeapon : public UGA_WeaponEquipBase
{
	GENERATED_BODY()

protected:
	virtual void HandleWeapon(AHeroWeaponBase* InWeapon) override;

private:
	// 캐릭터에 무기 전용 AnimLayer를 연결.
	void LinkWeaponAnimLayer(const TSubclassOf<UCharacterAnimLayer>& InAnimLayer);

	// 무기 입력 매핑 컨텍스트를 로컬 플레이어에 추가.
	void AddWeaponMappingContext(UInputMappingContext* InMappingContext);

	// 무기 기본 어빌리티를 부여하고, 반환된 핸들을 무기에 저장(해제 시 제거용).
	void GrantWeaponAbilities(AHeroWeaponBase* InWeapon, const TArray<FHeroAbilitySet>& InAbilitySets);
};
