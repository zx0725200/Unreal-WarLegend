// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "Component/EnemyCombatComponent.h"
#include "DataAsset/CommonAbilityConfigBase.h"
#include "Engine/AssetManager.h"
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
	
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
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

// DataConfig 비동기 로드 후 어빌리티 부여 - 로드 완료 전까지 ASC에 어빌리티 없음
void AEnemyCharacter::Init()
{
	if (DataConfig.IsNull())
	{
		return;
	}
	
	UAssetManager::GetStreamableManager().RequestAsyncLoad(DataConfig.ToSoftObjectPath(), 
		FStreamableDelegate::CreateLambda(
		[this]()
			{
				if (auto Data = DataConfig.Get())
				{
					Data->GiveAbilityToComponent(HeroAbilitySystemComponent);
				}
			}
		));
}



