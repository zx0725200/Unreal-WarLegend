// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitFlashComponent.generated.h"

class UAbilitySystemComponent;
class UMeshComponent;
class UMaterialInterface;
struct FOnAttributeChangeData;

/**
 * 소유 액터의 CurrentHp 가 줄어들면(=피격) 메시의 모든 머티리얼 슬롯을 짧게
 * FlashMaterial 로 교체했다가 복원해 '번쩍'이는 피격 피드백을 준다.
 * GAS 데미지면 출처 무관(플레이어 공격/도트 등)하게 동작.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class WARLEGEND_API UHitFlashComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHitFlashComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void OnHpChanged(const FOnAttributeChangeData& Data);

	void StartFlash();
	void EndFlash();

	UMeshComponent* ResolveMesh() const;

public:
	// 피격 시 잠깐 씌울 머티리얼(언릿 이미시브 추천). 비우면 동작 안 함.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitFlash")
	TObjectPtr<UMaterialInterface> FlashMaterial;

	// 번쩍이는 지속 시간(초).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitFlash")
	float FlashDuration = 0.12f;

private:
	UPROPERTY(Transient)
	TObjectPtr<UMeshComponent> CachedMesh;

	// 번쩍 동안 잠깐 교체했다가 되돌릴 원본 머티리얼(슬롯별).
	UPROPERTY(Transient)
	TArray<TObjectPtr<UMaterialInterface>> OriginalMaterials;

	TWeakObjectPtr<UAbilitySystemComponent> CachedASC;
	FDelegateHandle HpChangedHandle;
	FTimerHandle FlashTimer;
};
