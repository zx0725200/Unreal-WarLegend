// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/HeroAttributeSet.h"
#include "GameplayEffectExtension.h"

void UHeroAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetCurrentHpAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHp(), 0.f, GetMaxHp());
		
		SetCurrentHp(NewCurrentHealth);
	}
	
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHp();
		const float DamageTake = GetDamageTaken();
		
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageTake, 0.f, GetMaxHp());
		
		SetCurrentHp(NewCurrentHealth);
		
		const FString DebugString = FString::Printf(TEXT("Old Health : %f, Damage Taken : %f, Hp : %f"),OldHealth, DamageTake, NewCurrentHealth);
		
		UE_LOG(LogTemp, Error, TEXT("%s"), *DebugString);
		
		// UI에 전달
		
		
		
		// 죽음
		if (NewCurrentHealth == 0.f)
		{
			
		}
	}
}

UHeroAttributeSet::UHeroAttributeSet()
{
	InitCurrentHp(1.f);
	InitMaxHp(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}
