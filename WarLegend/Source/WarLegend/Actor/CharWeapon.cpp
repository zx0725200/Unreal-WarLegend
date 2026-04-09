#include "CharWeapon.h"


void ACharWeapon::SetAbilityHandleList(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	AbilityHandleList = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> ACharWeapon::GetAbilityHandleList() const
{
	return AbilityHandleList;
}
