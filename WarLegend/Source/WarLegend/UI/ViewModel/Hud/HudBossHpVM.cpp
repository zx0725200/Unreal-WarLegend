// Fill out your copyright notice in the Description page of Project Settings.


#include "HudBossHpVM.h"

#include "AbilitySystemComponent.h"
#include "Ability/HeroAttributeSet.h"
#include "Character/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

void UHudBossHpVM::Init()
{
	Super::Init();

	UWorld* World = GetOuter() ? GetOuter()->GetWorld() : nullptr;
	if (!World) return;

	AEnemyCharacter* Boss = Cast<AEnemyCharacter>(UGameplayStatics::GetActorOfClass(World, AEnemyCharacter::StaticClass()));
	if (!Boss) return;

	UAbilitySystemComponent* BossASC = Boss->GetAbilitySystemComponent();
	if (!BossASC) return;

	CachedASC = BossASC;

	SetMaxHp(BossASC->GetNumericAttribute(UHeroAttributeSet::GetMaxHpAttribute()));
	SetCurrentHp(BossASC->GetNumericAttribute(UHeroAttributeSet::GetCurrentHpAttribute()));

	CurrentHpHandle = BossASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetCurrentHpAttribute()
	).AddUObject(this, &UHudBossHpVM::HandleCurrentHpChanged);

	MaxHpHandle = BossASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetMaxHpAttribute()
	).AddUObject(this, &UHudBossHpVM::HandleMaxHpChanged);
}

void UHudBossHpVM::ClearBinding()
{
	if (CachedASC.IsValid())
	{
		CachedASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetCurrentHpAttribute()).Remove(CurrentHpHandle);
		CachedASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetMaxHpAttribute()).Remove(MaxHpHandle);
	}

	CachedASC.Reset();
}

void UHudBossHpVM::SetCurrentHp(float InValue)
{
	if (FMath::IsNearlyEqual(CurrentHp, InValue)) return;
	CurrentHp = InValue;
	OnCurrentHpChange.Broadcast(CurrentHp);
	SetHpRatio(MaxHp > 0.f ? CurrentHp / MaxHp : 0.f);
}

void UHudBossHpVM::SetMaxHp(float InValue)
{
	if (FMath::IsNearlyEqual(MaxHp, InValue)) return;
	MaxHp = InValue;
	OnMaxHpChange.Broadcast(MaxHp);
	SetHpRatio(MaxHp > 0.f ? CurrentHp / MaxHp : 0.f);
}

void UHudBossHpVM::SetHpRatio(float InValue)
{
	if (FMath::IsNearlyEqual(HpRatio, InValue)) return;
	HpRatio = InValue;
	OnHpRatioChanged.Broadcast(HpRatio);
}

void UHudBossHpVM::HandleCurrentHpChanged(const FOnAttributeChangeData& Data)
{
	SetCurrentHp(Data.NewValue);
}

void UHudBossHpVM::HandleMaxHpChanged(const FOnAttributeChangeData& Data)
{
	SetMaxHp(Data.NewValue);
}
