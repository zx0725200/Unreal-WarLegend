#pragma once

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None,
	Weapon		UMETA(DisplayName="Weapon"),
	Armor		UMETA(DisplayName="Armor"),
	Glove		UMETA(DisplayName="Glove"),
	
	BossWeapon	UMETA(DisplayName="BossWeapon"),
	BossArmor	UMETA(DisplayName="BossArmor"),
};

UENUM(BlueprintType)
enum class EItemGrade : uint8
{
	None,
	Normal		UMETA(DisplayName="Normal"),
	Rare		UMETA(DisplayName="Rare"),
	Unique		UMETA(DisplayName="Unique"),
	Legend		UMETA(DisplayName="Legend"),
	Epic		UMETA(DisplayName="Epic"),
};

UENUM(BlueprintType)
enum class EItemEquipType : uint8
{
	None,
	EquipItem	UMETA(DisplayName="EquipItem"),
	BossItem	UMETA(DisplayName="BossItem"),
};

UENUM(BlueprintType)
enum class EPlayerLocType : uint8
{
	None,
	Battle	UMETA(DisplayName="Battle"),
	City	UMETA(DisplayName="City"),
};

UENUM(BlueprintType)
enum class ECharAbilityApplyType : uint8
{
	OnTriggered,
	OnGiven
};

UENUM()
enum class EAbilityGiveMode : uint8
{
	GiveOnly,
	GiveAndActivateOnce
};

UENUM()
enum class EConfirmType : uint8
{
	Successful = 0,
	Failed
};