// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMeleeHitNotify.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GenericTeamAgentInterface.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ETC/Define.h"

void UBossMeleeHitNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	VALID_RETURN(MeshComp);

	AActor* MyOwner = MeshComp->GetOwner();
	VALID_RETURN(MyOwner);

	UWorld* World = MyOwner->GetWorld();
	VALID_RETURN(World);

	// ? 멀티 대비: 데미지는 서버에서만 발생. (스탠드얼론/PIE는 true)
	if (!MyOwner->HasAuthority())
	{
		return;
	}

	if (!HitEventTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("[BossMeleeHitNotify] HitEventTag 가 설정되지 않음."));
		return;
	}

	// ? 트레이스 시작/끝 지점 계산.
	const FVector Start = StartSocketName.IsNone()
		? MyOwner->GetActorLocation()
		: MeshComp->GetSocketLocation(StartSocketName);
	const FVector End = Start + MyOwner->GetActorForwardVector() * TraceLength;

	const FCollisionShape Sphere = FCollisionShape::MakeSphere(TraceRadius);
	FCollisionQueryParams Params(FName(TEXT("BossMeleeHit")), false, MyOwner);

	TArray<FHitResult> Hits;
	World->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, ECC_Pawn, Sphere, Params);

#if ENABLE_DRAW_DEBUG
	if (bDrawDebug)
	{
		DrawDebugSphere(World, Start, TraceRadius, 12, FColor::Red, false, 1.f);
		DrawDebugSphere(World, End, TraceRadius, 12, FColor::Green, false, 1.f);
		DrawDebugLine(World, Start, End, FColor::Yellow, false, 1.f, 0, 1.f);
	}
#endif

	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MyOwner);

	TArray<AActor*> AlreadyHit;
	for (const FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (!HitActor || HitActor == MyOwner || AlreadyHit.Contains(HitActor))
		{
			continue;
		}

		// ? 적대 팀(플레이어)만 타격.
		if (FGenericTeamId::GetAttitude(MyOwner, HitActor) != ETeamAttitude::Hostile)
		{
			continue;
		}

		// ? ASC 가 있는 대상만(데미지 적용 가능).
		if (!UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitActor))
		{
			continue;
		}

		AlreadyHit.Add(HitActor);

		// ? 근접 스윕은 보통 '시작부터 겹침(bStartPenetrating)' 상태라
		// ? ImpactPoint 가 트레이스 시작점(=보스 위치)으로 잡힌다.
		// ? 그대로 쓰면 이펙트가 보스에서 떠버리므로 타겟 기준으로 보정한다.
		FHitResult HitForCue = Hit;
		if (Hit.bStartPenetrating || Hit.ImpactPoint.IsNearlyZero())
		{
			const FVector TargetCenter = HitActor->GetActorLocation();
			// ? 보스 -> 타겟 방향으로 캡슐 표면쯤(살짝 보스 쪽)에 맞춘다.
			const FVector ToBoss = (MyOwner->GetActorLocation() - TargetCenter).GetSafeNormal2D();
			HitForCue.ImpactPoint = TargetCenter + ToBoss * 40.f;
			HitForCue.Location = HitForCue.ImpactPoint;
			HitForCue.ImpactNormal = ToBoss;
			HitForCue.Normal = ToBoss;
		}
		// ? 접점이 살짝 낮게 느껴져서 이펙트를 위로 올림.
		HitForCue.ImpactPoint.Z += 50.f;
		HitForCue.Location.Z += 50.f;
		// ? GameplayCue 가 HitResult 를 '유효한 충돌'로 인정하게(안 켜면 타겟 위치로 폴백).
		HitForCue.bBlockingHit = true;

		// [디버그] 코드가 보내는 실제 이펙트 좌표. 이 구체 != 이펙트 위치면 원인은 큐 BP.
		DrawDebugSphere(World, HitForCue.ImpactPoint, 15.f, 12, FColor::Cyan, false, 2.f);

		// ? GA_BossAttack 이 HitResult 를 GameplayCue 위치로 쓰므로 Context 에 담아 전달.
		FGameplayEffectContextHandle Ctx = SourceASC ? SourceASC->MakeEffectContext() : FGameplayEffectContextHandle();
		Ctx.AddHitResult(HitForCue);

		FGameplayEventData Payload;
		Payload.EventTag = HitEventTag;
		Payload.Instigator = MyOwner;
		Payload.Target = HitActor;
		Payload.ContextHandle = Ctx;

		// ? GA_BossAttack 의 WaitGameplayEvent 로 전달.
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MyOwner, HitEventTag, Payload);
	}
}
