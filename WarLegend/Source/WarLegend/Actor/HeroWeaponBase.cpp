#include "HeroWeaponBase.h"

#include "Components/BoxComponent.h"

AHeroWeaponBase::AHeroWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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

