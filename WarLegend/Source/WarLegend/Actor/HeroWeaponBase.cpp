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
		
	}
}

void AHeroWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	VALID_RETURN(WeaponOwningPawn);
	
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		
	}
}

