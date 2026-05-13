// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroWeaponNotifyState.h"

#include "Component/PawnCombatComponentBase.h"
#include "ETC/Define.h"
#include "ETC/HeroFunctionLibrary.h"

void UHeroWeaponNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	// ? 애니메이션 재생중 Notify가 들어오면 실행됨.
	// ? 애니메이션에서 따로 추가 해줘야함.
	
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	ToggleWeaponCollision(MeshComp, ECollisionEnabled::Type::QueryOnly);
}

void UHeroWeaponNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	
	ToggleWeaponCollision(MeshComp, ECollisionEnabled::Type::NoCollision);
}

void UHeroWeaponNotifyState::ToggleWeaponCollision(const USkeletalMeshComponent* InMeshComp, const ECollisionEnabled::Type InCollisionType)
{
	VALID_RETURN(InMeshComp);
	
	AActor* MyOwner = InMeshComp->GetOwner();
	VALID_RETURN(MyOwner);
	
	UPawnCombatComponentBase* CombatComp = UHeroFunctionLibrary::GetPawnCombatComponentFromActor(MyOwner);
	VALID_RETURN(CombatComp);
	
	CombatComp->ToggleWeaponCollision(InCollisionType);
}
