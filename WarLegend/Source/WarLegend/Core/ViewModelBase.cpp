// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewModelBase.h"
#include "TableManager.h"
#include "UIManager.h"
#include "GachaManager.h"
#include "SaveGameDataManager.h"
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

UGameInstance* UViewModelBase::GetGameInstance() const
{
	const UWorld* World = GetMyWorld();
	if (!World)
	{
		return nullptr;
	}
	UGameInstance* GameInstance = World->GetGameInstance();
	if (!GameInstance)
	{
		return nullptr;
	}
	
	return GameInstance;
}

ULocalPlayer* UViewModelBase::GetLocalPlayer() const
{
	const UWorld* World = GetMyWorld();
	if (!World)
	{
		return nullptr;
	}
	ULocalPlayer* LocalPlayer = World->GetFirstLocalPlayerFromController();
	if (!LocalPlayer)
	{
		return nullptr;
	}
	
	return LocalPlayer;
}

UTableManager* UViewModelBase::GetTableManager() const
{
	const UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
	{
		return nullptr;
	}
	
	return GameInstance->GetSubsystem<UTableManager>();
}

UInventoryManager* UViewModelBase::GetInvenManager() const
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer)
	{
		return nullptr;
	}
	
	return LocalPlayer->GetSubsystem<UInventoryManager>();
}

UUIManagerImpl* UViewModelBase::GetUIManager() const
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!LocalPlayer)
	{
		return nullptr;
	}
	
	return LocalPlayer->GetSubsystem<UIManager>()->MgrImpl;
}

UGachaManager* UViewModelBase::GetGachaManager() const
{
	const UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
	{
		return nullptr;
	}
	
	return GameInstance->GetSubsystem<UGachaManager>();
}

USaveGameDataManager* UViewModelBase::GetSaveGameDataManager() const
{
	const UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
	{
		return nullptr;
	}
	
	return GameInstance->GetSubsystem<USaveGameDataManager>();
}
