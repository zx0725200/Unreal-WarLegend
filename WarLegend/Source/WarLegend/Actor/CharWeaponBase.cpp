#include "CharWeaponBase.h"

#include "Components/BoxComponent.h"

ACharWeaponBase::ACharWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACharWeaponBase::SetAbilityHandleList(const TArray<FGameplayAbilitySpecHandle>& InSpecHandleList)
{
	AbilityHandleList = InSpecHandleList;
}

UBoxComponent* ACharWeaponBase::GetWeaponCollisionBox()
{
	return WeaponCollisionBox;
}

TArray<FGameplayAbilitySpecHandle> ACharWeaponBase::GetAbilityHandleList() const
{
	return AbilityHandleList;
}

