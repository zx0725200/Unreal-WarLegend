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
 * 소유 액터의 CurrentHp 가 줄어들면(=피격) 메시에 짧게 오버레이 머티리얼을 씌웠다가
 * 벗겨서 '번쩍'이는 피격 피드백을 준다. 원본 머티리얼/텍스처는 그대로 두고 그 위에
 * 한 번 더 렌더링되므로 보스가 단색으로 사라져 보이지 않고 빨간 톤만 살짝 입혀진다.
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
	// 피격 시 원본 위에 잠깐 덧씌울 오버레이 머티리얼(반투명/애디티브 빨강 추천).
	// 비우면 동작 안 함. 살짝만 붉게 하려면 오버레이 머티리얼의 불투명도/이미시브를 낮춘다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitFlash")
	TObjectPtr<UMaterialInterface> FlashMaterial;

	// 번쩍이는 지속 시간(초).
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HitFlash")
	float FlashDuration = 0.12f;

private:
	UPROPERTY(Transient)
	TObjectPtr<UMeshComponent> CachedMesh;

	TWeakObjectPtr<UAbilitySystemComponent> CachedASC;
	FDelegateHandle HpChangedHandle;
	FTimerHandle FlashTimer;
};
