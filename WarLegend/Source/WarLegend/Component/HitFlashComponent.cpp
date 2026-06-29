// Fill out your copyright notice in the Description page of Project Settings.


#include "HitFlashComponent.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/MeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Ability/Attribute/HeroAttributeSet.h"

UHitFlashComponent::UHitFlashComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHitFlashComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!Owner) return;

	// 소유 액터의 ASC 확보 (HeroAbilitySystemComponent).
	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Owner))
	{
		CachedASC = ASI->GetAbilitySystemComponent();
	}

	CachedMesh = ResolveMesh();

	if (CachedASC.IsValid())
	{
		// CurrentHp 가 바뀔 때마다 호출. 감소면 번쩍.
		HpChangedHandle = CachedASC->GetGameplayAttributeValueChangeDelegate(
			UHeroAttributeSet::GetCurrentHpAttribute()
		).AddUObject(this, &UHitFlashComponent::OnHpChanged);
	}
}

void UHitFlashComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(FlashTimer);
	}

	if (CachedASC.IsValid() && HpChangedHandle.IsValid())
	{
		CachedASC->GetGameplayAttributeValueChangeDelegate(
			UHeroAttributeSet::GetCurrentHpAttribute()).Remove(HpChangedHandle);
	}
	HpChangedHandle.Reset();

	// 번쩍 도중 종료되면 원본 머티리얼이 남도록 복원.
	if (CachedMesh && OriginalMaterials.Num() > 0)
	{
		for (int32 i = 0; i < OriginalMaterials.Num(); ++i)
		{
			CachedMesh->SetMaterial(i, OriginalMaterials[i]);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void UHitFlashComponent::OnHpChanged(const FOnAttributeChangeData& Data)
{
	// HP 가 줄었을 때만(피격). 힐/초기화는 무시.
	if (Data.NewValue < Data.OldValue - KINDA_SMALL_NUMBER)
	{
		StartFlash();
	}
}

void UHitFlashComponent::StartFlash()
{
	if (!FlashMaterial || !CachedMesh) return;

	// 원본 머티리얼을 최초 1회만 캐시(번쩍 중 또 맞아도 덮어쓰지 않게).
	if (OriginalMaterials.Num() == 0)
	{
		const int32 Num = CachedMesh->GetNumMaterials();
		OriginalMaterials.Reserve(Num);
		for (int32 i = 0; i < Num; ++i)
		{
			OriginalMaterials.Add(CachedMesh->GetMaterial(i));
		}
	}

	// 모든 슬롯을 플래시 머티리얼로 교체 → 메시 전체가 그 색으로 번쩍.
	for (int32 i = 0; i < OriginalMaterials.Num(); ++i)
	{
		CachedMesh->SetMaterial(i, FlashMaterial);
	}

	UWorld* World = GetWorld();
	if (!World) return;

	// 연타로 다시 맞으면 타이머가 갱신돼 번쩍이 자연스럽게 이어진다.
	World->GetTimerManager().SetTimer(
		FlashTimer, this, &UHitFlashComponent::EndFlash, FlashDuration, /*bLoop*/ false);
}

void UHitFlashComponent::EndFlash()
{
	if (!CachedMesh) return;

	// 원본 머티리얼 복원.
	for (int32 i = 0; i < OriginalMaterials.Num(); ++i)
	{
		CachedMesh->SetMaterial(i, OriginalMaterials[i]);
	}
}

UMeshComponent* UHitFlashComponent::ResolveMesh() const
{
	// 캐릭터면 본체 스켈레탈 메시 우선.
	if (const ACharacter* OwnerChar = Cast<ACharacter>(GetOwner()))
	{
		if (UMeshComponent* CharMesh = OwnerChar->GetMesh())
		{
			return CharMesh;
		}
	}
	// 그 외엔 첫 메시 컴포넌트.
	return GetOwner() ? GetOwner()->FindComponentByClass<UMeshComponent>() : nullptr;
}
