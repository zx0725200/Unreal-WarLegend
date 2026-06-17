#include "HeroWeaponBase.h"

#include "Components/BoxComponent.h"
#include "ETC/Define.h"

AHeroWeaponBase::AHeroWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this,&ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this,&ThisClass::OnCollisionBoxEndOverlap);
}

void AHeroWeaponBase::SetAbilityHandleList(const TArray<FGameplayAbilitySpecHandle>& InSpecHandleList)
{
	AbilityHandleList = InSpecHandleList;
}

UBoxComponent* AHeroWeaponBase::GetWeaponCollisionBox()
{
	return WeaponCollisionBox;
}

TArray<FGameplayAbilitySpecHandle> AHeroWeaponBase::GetAbilityHandleList() const
{
	return AbilityHandleList;
}

void AHeroWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	VALID_RETURN(WeaponOwningPawn);

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (WeaponOwningPawn != HitPawn)
		{
			FHitResult HitResult = SweepResult;

			// ? 오버랩은 스윕이 아니라서 SweepResult 가 비어있다(ImpactPoint = 0).
			// ? 무기 박스 위치를 타겟 충돌면에 투영해 실제 접점을 만든다.
			if (!bFromSweep)
			{
				const FVector WeaponLocation = WeaponCollisionBox->GetComponentLocation();
				FVector ClosestPoint = WeaponLocation;

				if (!OtherComp || OtherComp->GetClosestPointOnCollision(WeaponLocation, ClosestPoint) < 0.f)
				{
					ClosestPoint = WeaponLocation;
				}

				HitResult.ImpactPoint = ClosestPoint;
				HitResult.Location = ClosestPoint;
				HitResult.ImpactNormal = (WeaponLocation - ClosestPoint).GetSafeNormal();
				HitResult.Normal = HitResult.ImpactNormal;
				// ? GameplayCue 가 HitResult 를 '유효한 충돌'로 인정해야(bBlockingHit)
				// ? ImpactPoint 를 이펙트 위치로 쓴다. 안 켜면 타겟 액터 위치로 폴백됨.
				HitResult.bBlockingHit = true;
			}

			OnWeaponHitTarget.ExecuteIfBound(OtherActor, HitResult);
		}
	}
}

void AHeroWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	VALID_RETURN(WeaponOwningPawn);
	
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (WeaponOwningPawn != HitPawn)
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}

