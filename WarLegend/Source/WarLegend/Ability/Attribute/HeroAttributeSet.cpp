// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAttributeSet.h"
#include "GameplayEffectExtension.h"

// ? ExecutionCalculation을 상속받는 UGE_DamageToken 에서 게임플레이 이펙트가 실행되고 실행
// ? Instant를 통해 Attribute가 변경됐을 때
// ? Periodic tick마다 적용됐을때.
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
	InitCurrentHp(10000.f);
	InitMaxHp(10000.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}
