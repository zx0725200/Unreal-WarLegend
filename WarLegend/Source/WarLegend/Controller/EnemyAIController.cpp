// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ETC/Define.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"


AEnemyAIController::AEnemyAIController()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	SetPerceptionComponent(*Perception);
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = 2000.f;
	SightConfig->PeripheralVisionAngleDegrees = 180.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

	Perception->ConfigureSense(*SightConfig);
	Perception->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdated);

	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	VALID_RETURN(BTAsset);
	RunBehaviorTree(BTAsset);
}

void AEnemyAIController::OnUnPossess()
{
	if (UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent))
	{
		BTComp->StopTree();
	}
	
	Super::OnUnPossess();
}

void AEnemyAIController::OnTargetPerceptionUpdated(AActor* InActor, FAIStimulus InStimulus)
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (InActor != PlayerPawn)
	{
		return;
	}
	
	UBlackboardComponent* BB = GetBlackboardComponent();
	VALID_RETURN(BB);
	
	//Sight를 쓰려면 플레이어 쪽에 AIPerceptionStimuliSourceComponent 등록이 필요하다. 
	//또는 RegisterAllPawnsAsSources 옵션. 빼먹으면 절대 감지 안 된다.
	
	if (InStimulus.WasSuccessfullySensed())
	{
		BB->SetValueAsObject(TEXT("TargetActor"), InActor);
	}
	else
	{
		// 시야에서 완전히 사라진 경우 타겟 클리어
		AActor* Current = Cast<AActor>(BB->GetValueAsObject(TEXT("TargetActor")));
		if (Current == InActor)
		{
			BB->ClearValue(TEXT("TargetActor"));
		}
	}
}

