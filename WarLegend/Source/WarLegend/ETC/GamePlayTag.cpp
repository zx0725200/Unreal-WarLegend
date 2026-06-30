#include "GamePlayTag.h"


namespace GamePlayTag
{
	UE_DEFINE_GAMEPLAY_TAG(Battle_Move, "Battle.Move");
	UE_DEFINE_GAMEPLAY_TAG(Battle_Look, "Battle.Look");
	UE_DEFINE_GAMEPLAY_TAG(Battle_Equip, "Battle.EquipWeapon");
	UE_DEFINE_GAMEPLAY_TAG(Battle_UnEquip, "Battle.UnEquipWeapon");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Axe,"Battle.LightAttack.Weapon");
	
	// 플레이어 태그
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe, "Player.Weapon.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Axe, "Player.Event.Equip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_Axe, "Player.Event.UnEquip.Axe");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_Attack, "Player.SetByCaller.Attack");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe,"Player.Ability.Equip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Axe,"Player.Ability.Unequip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Axe,"Player.Ability.Attack.Light.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Parry,"Player.Ability.Parry");

	UE_DEFINE_GAMEPLAY_TAG(Battle_Parry,"Battle.Parry");
	UE_DEFINE_GAMEPLAY_TAG(Player_State_Parrying,"Player.State.Parrying");
	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Attack_NormalA, "Enemy.Ability.Attack.NormalA");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Attack_NormalB, "Enemy.Ability.Attack.NormalB");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Attack_Magic, "Enemy.Ability.Attack.Magic");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Attack_Combo, "Enemy.Ability.Attack.Combo");
	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_State_Attacking, "Enemy.State.Attacking");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_State_Moving, "Enemy.State.Moving");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_State_Dead, "Enemy.State.Attacking");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_State_Groggy, "Enemy.State.Groggy");
	
	UE_DEFINE_GAMEPLAY_TAG(GamePlayCue_Melee_Hit,"GameplayCue.Melee.Hit");
	UE_DEFINE_GAMEPLAY_TAG(GamePlayCue_Parry,"GameplayCue.Parry");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_PlayerHit,"Shared.Event.PlayerHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit,"Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_BaseDamage,"Shared.Event.BaseDamage");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_ParrySuccess,"Shared.Event.ParrySuccess");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_BossStagger,"Shared.Event.BossStagger");
}