// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ViewModelBase.h"
#include "DataTable/DungeonTableData.h"
#include "SlotDungeonVM.generated.h"

struct FDungeonTableData;

UCLASS()
class WARLEGEND_API USlotDungeonVM : public UViewModelBase
{
	GENERATED_BODY()
	
public:
	void Init(const FDungeonTableData& InData);
	
	void OnEnterDungeon();    // 던전 입장
	void OnExitDungeon();     // 던전 퇴장
	
	const FDungeonTableData& GetData() const { return Data; }

private:
	FDungeonTableData Data;
};
