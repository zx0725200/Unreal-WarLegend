// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability/GE_DamageToken.h"

#include "Attribute/HeroAttributeSet.h"
#include "ETC/GamePlayTag.h"

struct FHeroDamageCapture
{
	// Execute_Implementation에서 GameplayEffectExecutionCalculation 파라미터에서 캡처된 속성값을 가져올수 있게 함.
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FHeroDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHeroAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHeroAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UHeroAttributeSet, DamageTaken, Target, false)
	}
};

static const FHeroDamageCapture& GetHeroDamageCapture()
{
	static FHeroDamageCapture WarriorDamageCapture;
	return WarriorDamageCapture;
}

UGE_DamageToken::UGE_DamageToken()
{
	// 속성 캡처 초기화
	RelevantAttributesToCapture.Add(GetHeroDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetHeroDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetHeroDamageCapture().DamageTakenDef);
}

// !흐름 : 데미지 계산.
void UGE_DamageToken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetHeroDamageCapture().AttackPowerDef,EvaluateParameters,SourceAttackPower);

	float BaseDamage = 0.f;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(GamePlayTag::Shared_Event_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}
	}
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetHeroDamageCapture().DefensePowerDef,EvaluateParameters,TargetDefensePower);
	
	if (BaseDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetHeroDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				BaseDamage
			)
		);
	}
}
