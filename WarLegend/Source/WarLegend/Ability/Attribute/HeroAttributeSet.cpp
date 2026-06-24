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
		const float DamageTake = GetDamageTaken();

		// ? 메타 어트리뷰트는 사용 후 0으로 리셋(누적 방지).
		SetDamageTaken(0.f);

		const float OldHealth = GetCurrentHp();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageTake, 0.f, GetMaxHp());

		SetCurrentHp(NewCurrentHealth);

		AActor* Owner = GetOwningActor();
		// 죽음
		if (GetCurrentHp() <= 0.f)
		{

		}
	}
}

UHeroAttributeSet::UHeroAttributeSet()
{
	InitCurrentHp(100.f);
	InitMaxHp(100.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}
