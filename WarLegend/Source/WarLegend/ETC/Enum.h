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

// 등급 필터를 어디에 적용할지 구분 (가챠 결과 필터 / 인벤토리 버리기 필터)
UENUM()
enum class EFilterType : uint8
{
	Gacha,
	Discard
};

// 인벤토리 정렬 방향
UENUM()
enum class ESortOrder : uint8
{
	Descending,	// 내림차순 (높은 등급/스탯 먼저)
	Ascending	// 오름차순
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