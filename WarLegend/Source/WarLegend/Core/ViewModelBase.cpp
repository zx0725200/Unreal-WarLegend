// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModelBase.h"
#include "TableManager.h"
#include "InventoryManager.h"

void UViewModelBase::Init()
{
}

UWorld* UViewModelBase::GetMyWorld() const
{
	// 기본객체나 외부 데이터라면 nullptr
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return nullptr;
	}

	// 나를 만든 주인(Outer)에게 월드를 물어봅니다.
	if (GetOuter())
	{
		return GetOuter()->GetWorld();
	}
	
	return nullptr;
}

UTableManager* UViewModelBase::GetTableManager() const
{
	UWorld* World = GetMyWorld();
	if (!World)
	{
		return nullptr;
	}
	UGameInstance* GameInstance = GetMyWorld()->GetGameInstance();
	if (!GameInstance)
	{
		return nullptr;
	}
	
	return World->GetGameInstance()->GetSubsystem<UTableManager>();
}

UInventoryManager* UViewModelBase::GetInvenManager() const
{
	UWorld* World = GetMyWorld();
	if (!World)
	{
		return nullptr;
	}
	ULocalPlayer* LocalPlayer = GetMyWorld()->GetFirstLocalPlayerFromController();
	if (!LocalPlayer)
	{
		return nullptr;
	}
	
	return LocalPlayer->GetSubsystem<UInventoryManager>();
}
