#pragma once

#include "GameFramework/GameplayMessageSubsystem.h"

#define GTGetMgrImpl(SubSystemClassName) (GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<SubSystemClassName>()->MgrImpl : nullptr)
#define GTGetMgr(SubSystemClassName) (GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<SubSystemClassName>() : nullptr)
#define GTUIGetMgr(SubSystemClassName) (GetOwningLocalPlayer() ? GetOwningLocalPlayer()->GetSubsystem<SubSystemClassName>() : nullptr)
#define GTUIGetMgrImpl(SubSystemClassName) (GetOwningLocalPlayer() ? GetOwningLocalPlayer()->GetSubsystem<SubSystemClassName>()->MgrImpl : nullptr)

#define EVENT_LISTEN(EventNameLiteral, MsgType, Obj, Func) \
(Obj)->UIEventHandle.Listen<MsgType>(FName(EventNameLiteral), (Obj), (Func))

#define EVENT_UNLISTEN(EventNameLiteral, Obj) \
(Obj)->UIEventHandle.Unlisten(FName(EventNameLiteral))

#define EVENT_UNLISTEN_ALL(Obj) \
(Obj)->UIEventHandle.UnlistenAll()

// Broadcast는 WorldContext가 필요해서 Obj를 같이 받는 형태로 해두는 게 안전함
#define EVENT_BROADCAST(EventNameLiteral, MsgType, Obj, MsgValue) \
do { \
MsgType __Msg = (MsgValue); \
__Msg.Name = FName(EventNameLiteral); \
const FGameplayTag __Channel = FWLUIEventHandle::UIChannel(); \
if (__Channel.IsValid()) \
{ \
UGameplayMessageSubsystem::Get((Obj)).BroadcastMessage<MsgType>(__Channel, __Msg); \
} \
} while(0)

template <typename T, typename = void>
struct THasIsValid : std::false_type {};

template <typename T>
struct THasIsValid<T, std::void_t<decltype(std::declval<T>().IsValid())>> : std::true_type {};

template <typename T>
FORCEINLINE bool CheckAnyValid(const T& Data)
{
	// 언리얼 오브젝트 확인
	// std::is_convertible_v 사용 하면 TObjectPtr -> 포인터로 변환
	if constexpr (std::is_convertible_v<T, const UObject*>)
	{
		return ::IsValid(Data);
	}
	// 일반 C++ 포인터 처리 (nullptr 체크)
	else if constexpr (std::is_pointer_v<T>)
	{
		return Data != nullptr;
	}
	// IsValid()가 있는 스마트 포인터 (WeakPtr, SharedPtr)
	else if constexpr (THasIsValid<T>::value)
	{
		return Data.IsValid();
	}
	// 그 외 (참조자, int, struct 등) null이 될 수 없으므로 무조건 true
	else
	{
		return true;
	}
}

template <typename... Args>
FORCEINLINE bool CheckAllValid(Args&&... args)
{
	return (CheckAnyValid(args) && ...);
}

#define VALID_RETURN(...) \
if (false == CheckAllValid(__VA_ARGS__)) \
{ \
	UE_LOG(LogTemp, Warning, TEXT("Valid check failed: %s [%s:%d]"), \
		*FString(__FUNCTION__), *FString(__FILE__), __LINE__); \
	return; \
}

#define GET_GUARD_RETURN(VarName, Expression) \
const auto VarName = Expression; \
if (false == CheckAnyValid(VarName)) { return; }

// Event

// MsgType에 .Name 멤버가 있는지 체크(SFINAE)
template<typename T, typename = void>
struct TWLHasNameMember : std::false_type {};

template<typename T>
struct TWLHasNameMember<T, std::void_t<decltype(std::declval<T>().Name)>> : std::true_type {};

struct FWLUIEventHandle
{
	// "이름" -> 핸들
	TMap<FName, FGameplayMessageListenerHandle> Handles;

	// UI 태그는 고정
	static FGameplayTag UIChannel()
	{
		// Project Settings > Gameplay Tags에 "UI" 등록돼 있어야 Valid=true
		static const FGameplayTag Tag = FGameplayTag::RequestGameplayTag(TEXT("UI"), /*ErrorIfNotFound*/false);
		return Tag;
	}

	template<typename MsgType, typename UserClass>
	FGameplayMessageListenerHandle Listen(
		FName EventName,
		UserClass* Obj,
		void (UserClass::*Func)(FGameplayTag, const MsgType&)
	)
	{
		static_assert(TIsDerivedFrom<UserClass, UObject>::Value, "Obj must be UObject-derived");
		static_assert(TWLHasNameMember<MsgType>::value, "MsgType must have member: FName Name");
		
		Unlisten(EventName);

		const FGameplayTag Channel = UIChannel();
		// 태그가 invalid면 아무 것도 안 올 거라서 조기 반환(디버그용)
		if (!Channel.IsValid())
		{
			return FGameplayMessageListenerHandle();
		}

		TWeakObjectPtr<UserClass> WeakObj(Obj);

		auto& MS = UGameplayMessageSubsystem::Get(Obj);
		FGameplayMessageListenerHandle Handle =
			MS.template RegisterListener<MsgType>(
				Channel,
				[WeakObj, EventName, Func](FGameplayTag InChannel, const MsgType& Msg)
				{
					if (!WeakObj.IsValid()) return;
					if (Msg.Name != EventName) return;

					(WeakObj.Get()->*Func)(InChannel, Msg);
				}
			);

		Handles.Add(EventName, Handle);
		return Handle;
	}

	void Unlisten(FName EventName)
	{
		if (FGameplayMessageListenerHandle* H = Handles.Find(EventName))
		{
			H->Unregister();
			Handles.Remove(EventName);
		}
	}

	void UnlistenAll()
	{
		for (auto& Pair : Handles)
		{
			Pair.Value.Unregister();
		}
		Handles.Empty();
	}

	template<typename MsgType>
	void Broadcast(FName EventName, MsgType MsgByValue)
	{
		static_assert(TWLHasNameMember<MsgType>::Value, "MsgType must have member: FName Name");

		MsgByValue.Name = EventName;

		const FGameplayTag Channel = UIChannel();
		if (!Channel.IsValid())
		{
			return;
		}

		UGameplayMessageSubsystem::Get(GWorld ? GWorld : (UObject*)nullptr);
	}
};