// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Component/EnemyCombatComponent.h"
#include "Component/HitFlashComponent.h"
#include "DataAsset/CommonAbilityConfigBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AEnemyCharacter::AEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 360.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 100.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	// 플레이어/다른 적과 캡슐이 서로 밀어내지 않게(공격 중 박아서 밀려나는 문제 방지).
	// 공격 히트 판정은 BossMeleeHitNotify 의 별도 트레이스라 영향 없음.
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	// 캡슐이 겹쳐도 무브먼트가 폭발적으로 튕겨내지 않도록 상한 축소(혹시 모를 잔여 침투 대비).
	GetCharacterMovement()->MaxDepenetrationWithPawn = 0.f;
	
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
	HitFlashComponent = CreateDefaultSubobject<UHitFlashComponent>("HitFlashComponent");
}

UAbilitySystemComponent* AEnemyCharacter::GetAbilitySystemComponent() const
{
	return Super::GetAbilitySystemComponent();
}

// AI 컨트롤러가 빙의할 때 엔진이 호출 - Super에서 ASC 초기화 후 Init으로 어빌리티 세팅 시작
void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	Init();
}

UPawnCombatComponentBase* AEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

void AEnemyCharacter::Init()
{
	if (DataConfig.IsNull())
	{
		return;
	}
	
	auto Data = DataConfig.LoadSynchronous();
	if (Data)
	{
		Data->GiveAbilityToComponent(HeroAbilitySystemComponent);
	}
}



