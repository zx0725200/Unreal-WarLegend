// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETC/Struct.h"
#include "GameFramework/SaveGame.h"
#include "WLSaveGame.generated.h"


enum class EItemGrade : uint8;
enum class EItemType : uint8;
/**
 *
 */
UCLASS()
class WARLEGEND_API UWLSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TMap<EItemGrade, bool> GachaFilter;

	// 인벤토리 "모두 버리기" 대상 등급 설정 (체크된 등급이 버려진다)
	UPROPERTY()
	TMap<EItemGrade, bool> DiscardFilter;

	UPROPERTY()
	TArray<FMyItem> InvenItemData;

	// 장착 아이템 (아이템 타입 -> 인벤토리 UniqueID)
	UPROPERTY()
	TMap<EItemType, int32> EquippedItemData;
};
