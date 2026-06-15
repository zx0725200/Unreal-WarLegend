#pragma once
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"

#include "Struct.generated.h"

class UHeroAbility;
class UInputMappingContext;
class UCharacterAnimLayer;
struct FItemTableData;
enum class EItemType : uint8;
enum class EItemGrade : uint8;

USTRUCT(Blueprintable)
struct FMyItem
{
	GENERATED_BODY()

	void Init(const FItemTableData* InTableData, const FLinearColor& InGradeColor, const int32 InUniqueID);

	// 능력치 합계 (정렬 / 업그레이드 비교용)
	int32 GetTotalStat() const { return HP + ATK + DEF; }

public:
	UPROPERTY()
	FName EventName;
	
	UPROPERTY()
	int32 UniqueID = 0;
	
	UPROPERTY()
	FName Name;
	
	UPROPERTY()
	int32 ID = 0;
	
	UPROPERTY()
	FString ItemName;
	
	UPROPERTY()
	FString ItemTypeName;
	
	UPROPERTY()
	FLinearColor ItemGradeColor;
	
	UPROPERTY()
	EItemType ItemType;
	
	UPROPERTY()
	EItemGrade ItemGrade;
	
	UPROPERTY()
	int32 HP = 0;
	
	UPROPERTY()
	int32 ATK = 0;
	
	UPROPERTY()
	int32 DEF = 0;
};

// 장착 중인 아이템들의 능력치 합산 값
USTRUCT(Blueprintable)
struct FEquipStatTotal
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int32 HP = 0;

	UPROPERTY()
	int32 ATK = 0;

	UPROPERTY()
	int32 DEF = 0;
};

USTRUCT(Blueprintable)
struct FGachaLogData
{
	GENERATED_BODY()

public:
	FString ItemGradeName;
	FString ItemName;
	FLinearColor GradeColor;
	FString Time;
};

USTRUCT(BlueprintType)
struct FHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "BattleTag"))
	FGameplayTag BattleTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UHeroAbility> AbilityToGrant;

	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UCharacterAnimLayer> WeaponAnimLayerToLink;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "Battle"))
	TArray<FHeroAbilitySet> DefaultWeaponAbilities;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;
};