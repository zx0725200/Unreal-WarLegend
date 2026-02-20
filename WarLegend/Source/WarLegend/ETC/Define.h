#pragma once

#define GTGetMgrImpl(SubSystemClassName) (GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<SubSystemClassName>()->MgrImpl : nullptr)
#define GTGetMgr(SubSystemClassName) (GetLocalPlayer() ? GetLocalPlayer()->GetSubsystem<SubSystemClassName>() : nullptr)
#define GTUIGetMgr(SubSystemClassName) (GetOwningLocalPlayer() ? GetOwningLocalPlayer()->GetSubsystem<SubSystemClassName>() : nullptr)
#define GTUIGetMgrImpl(SubSystemClassName) (GetOwningLocalPlayer() ? GetOwningLocalPlayer()->GetSubsystem<SubSystemClassName>()->MgrImpl : nullptr)

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
if (false == CheckAllValid(__VA_ARGS__)) { return; }

#define GET_GUARD_RETURN(VarName, Expression) \
const auto VarName = Expression; \
if (false == CheckAnyValid(VarName)) { return; }