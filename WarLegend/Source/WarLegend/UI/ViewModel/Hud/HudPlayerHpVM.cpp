// Fill out your copyright notice in the Description page of Project Settings.


#include "HudPlayerHpVM.h"

#include "AbilitySystemComponent.h"
#include "Ability/Attribute/HeroAttributeSet.h"
#include "Character/WarLegendCharacter.h"
#include "ETC/Define.h"
#include "Kismet/GameplayStatics.h"

void UHudPlayerHpVM::Init()
{
	Super::Init();

	UWorld* World = GetOuter() ? GetOuter()->GetWorld() : nullptr;
	VALID_RETURN(World);

	AWarLegendCharacter* Player = Cast<AWarLegendCharacter>(UGameplayStatics::GetPlayerPawn(World, 0));
	VALID_RETURN(Player);

	UAbilitySystemComponent* PlayerASC = Player->GetAbilitySystemComponent();
	VALID_RETURN(PlayerASC);

	CachedASC = PlayerASC;

	SetMaxHp(PlayerASC->GetNumericAttribute(UHeroAttributeSet::GetMaxHpAttribute()));
	SetCurrentHp(PlayerASC->GetNumericAttribute(UHeroAttributeSet::GetCurrentHpAttribute()));

	CurrentHpHandle = PlayerASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetCurrentHpAttribute()
	).AddUObject(this, &UHudPlayerHpVM::HandleCurrentHpChanged);

	MaxHpHandle = PlayerASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetMaxHpAttribute()
	).AddUObject(this, &UHudPlayerHpVM::HandleMaxHpChanged);
}

void UHudPlayerHpVM::ClearBinding()
{
	VALID_RETURN(CachedASC);

	CachedASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetCurrentHpAttribute()).Remove(CurrentHpHandle);
	CachedASC->GetGameplayAttributeValueChangeDelegate(UHeroAttributeSet::GetMaxHpAttribute()).Remove(MaxHpHandle);

	CachedASC.Reset();
}

void UHudPlayerHpVM::SetCurrentHp(const float InValue)
{
	if (FMath::IsNearlyEqual(CurrentHp, InValue)) return;

	CurrentHp = InValue;
	SetHpRatio(MaxHp > 0.f ? CurrentHp / MaxHp : 0.f);
}

void UHudPlayerHpVM::SetMaxHp(const float InValue)
{
	if (FMath::IsNearlyEqual(MaxHp, InValue)) return;

	MaxHp = InValue;
	SetHpRatio(MaxHp > 0.f ? CurrentHp / MaxHp : 0.f);
}

void UHudPlayerHpVM::SetHpRatio(const float InValue)
{
	if (FMath::IsNearlyEqual(HpRatio, InValue)) return;

	HpRatio = InValue;
	OnHpRatioChanged.Broadcast(HpRatio);
}

void UHudPlayerHpVM::HandleCurrentHpChanged(const FOnAttributeChangeData& Data)
{
	SetCurrentHp(Data.NewValue);
}

void UHudPlayerHpVM::HandleMaxHpChanged(const FOnAttributeChangeData& Data)
{
	SetMaxHp(Data.NewValue);
}
