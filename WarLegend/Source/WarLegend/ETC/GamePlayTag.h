#pragma once

#include "NativeGameplayTags.h"

namespace GamePlayTag
{
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Battle_Move);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Battle_Look);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Battle_EquipWeapon);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Battle_UnEquipWeapon);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Battle_LightAttack_Axe);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Battle_HeavyAttack_Axe);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Battle_Parry);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Battle_LockOn);

	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Parry);

	// 패링 윈도우가 열려있는 동안 부착되는 상태 태그. 보스 타격이 이 태그를 보면 데미지를 무효화한다.
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_Parrying);

	// 피격 리액션 중 부착. 공격/구르기 어빌리티가 이 태그를 ActivationBlockedTags 로 막아 행동 불가 시간을 만든다.
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_HitReacting);
	
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Attack_NormalA);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Attack_NormalB);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Attack_Magic);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Attack_Combo);
	
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_State_Attacking);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_State_Moving);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_State_Dead);

	// 패링당해 그로기(경직) 상태인 동안 부착. 보스 AI/공격 어빌리티가 이 태그를 보고 행동을 막을 수 있다.
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_State_Groggy);

	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);
	
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_Attack);
	
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquip_Axe);
	
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GamePlayCue_Melee_Hit);

	// 패링 성공 시 보스 위치에 터뜨리는 큐(이펙트/사운드). 매달 GE 가 없어 ExecuteGameplayCue 로 직접 발동.
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GamePlayCue_Parry);
	
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_PlayerHit);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_BaseDamage);

	// 패링이 성공했을 때 타겟(플레이어)에게 전송. 이펙트/사운드/보스 경직 등을 BP에서 후킹할 수 있다.
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_ParrySuccess);

	// 패링당한 보스 자신에게 전송. GA_BossStagger 가 이 이벤트로 트리거되어 공격을 끊고 그로기 모션을 재생한다.
	WARLEGEND_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_BossStagger);
}
