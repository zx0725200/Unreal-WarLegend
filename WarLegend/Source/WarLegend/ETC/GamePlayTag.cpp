#include "GamePlayTag.h"


namespace GamePlayTag
{
	UE_DEFINE_GAMEPLAY_TAG(Battle_Move, "Battle.Move");
	UE_DEFINE_GAMEPLAY_TAG(Battle_Look, "Battle.Look");
	UE_DEFINE_GAMEPLAY_TAG(Battle_Equip, "Battle.EquipWeapon");
	UE_DEFINE_GAMEPLAY_TAG(Battle_UnEquip, "Battle.UnEquipWeapon");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Axe,"Battle.LightAttack.Weapon");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Axe,"Battle.HeavyAttack.Weapon");
	
	// 플레이어 태그
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe, "Player.Weapon.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Axe, "Player.Event.Equip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_Axe, "Player.Event.UnEquip.Axe");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_Attack, "Player.SetByCaller.Attack");
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe,"Player.Ability.Equip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Axe,"Player.Ability.Unequip.Axe");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Axe,"Player.Ability.Attack.Light.Axe");
	
	UE_DEFINE_GAMEPLAY_TAG(GamePlayCue_Melee_Hit,"GameplayCue.Melee.Hit");
	
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit,"Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_BaseDamage,"Shared.Event.BaseDamage");
}