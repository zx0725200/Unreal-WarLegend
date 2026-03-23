// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotInventoryVM.h"

#include "DataTable/ItemTableData.h"

void USlotInventoryVM::Init(const FItemTableData* InTableData, const FLinearColor& InGradeColor)
{
	ID             = InTableData->ID;
	ItemName       = InTableData->ItemName;
	ItemTypeName   = InTableData->ItemTypeName;
	ItemType       = InTableData->ItemType;
	ItemGrade      = InTableData->ItemGrade;
	ItemGradeColor = InGradeColor;
	HP             = InTableData->HP;
	ATK            = InTableData->ATK;
	DEF            = InTableData->DEF;
}

FMyItem USlotInventoryVM::ToSaveData() const
{
	FMyItem Data;
	Data.ItemName		= ItemName;
	Data.ItemTypeName	= ItemTypeName;
	Data.ItemType		= ItemType;
	Data.ItemGrade		= ItemGrade;
	Data.ItemGradeColor	= ItemGradeColor;
	Data.HP				= HP;
	Data.ATK			= ATK;
	Data.DEF			= DEF;
	return Data;
}

void USlotInventoryVM::FromSaveData(const FMyItem& InData)
{
	UniqueID		= InData.UniqueID;
	ID				= InData.ID;
	ItemName		= InData.ItemName;
	ItemTypeName	= InData.ItemTypeName;
	ItemType		= InData.ItemType;
	ItemGrade		= InData.ItemGrade;
	ItemGradeColor	= InData.ItemGradeColor;
	HP				= InData.HP;
	ATK				= InData.ATK;
	DEF				= InData.DEF;
}
