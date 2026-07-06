// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroAttributeSet.h"
#include "GameplayEffectExtension.h"

// ? ExecutionCalculation을 상속받는 UGE_DamageToken 에서 게임플레이 이펙트가 실행되고 실행
// ? Instant를 통해 Attribute가 변경됐을 때
// ? Periodic tick마다 적용됐을때.
void UHeroAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	const FGameplayAttribute GameplayAttribute = Data.EvaluatedData.Attribute;
	const float OldHealth = GetCurrentHp();
	
	const bool bDamageTake = GameplayAttribute == GetDamageTakenAttribute();
	const bool bChangeHp = GameplayAttribute == GetCurrentHpAttribute();
	
	if (bDamageTake)
	{
		const float DamageTake = GetDamageTaken();
				
		SetDamageTaken(0.f);
		ChangeHp(OldHealth - DamageTake);
	}
	else if (bChangeHp)
	{
		ChangeHp(OldHealth);
	}
}

void UHeroAttributeSet::ChangeHp(const int32 InHp)
{
	const float NewCurrentHealth = FMath::Clamp(InHp, 0.f, GetMaxHp());
		
	SetCurrentHp(NewCurrentHealth);
}

UHeroAttributeSet::UHeroAttributeSet()
{
	InitCurrentHp(100.f);
	InitMaxHp(100.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}
