// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonManager.h"

#include "TableManager.h"
#include "Actor/WLPatrolPathActor.h"
#include "Character/Monster.h"
#include "Character/WarLegendCharacter.h"
#include "DataTable/DungeonTableData.h"
#include "ETC/Constant.h"
#include "ETC/Enum.h"
#include "Kismet/GameplayStatics.h"

void UDungeonManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	MonsterClass = LoadClass<AMonster>(nullptr, TEXT("/Game/WarLegend/BP_Monster.BP_Monster_C"));
}

void UDungeonManager::InitDungeonSetting()
{
	if (!MonsterClass) return;
 
	SpawnedCount = 0;
	MonsterList.Empty();
 
	if (SpawnTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UDungeonManager::SpawnMonster, Constant::MonsterSpawnInterval, true, Constant::MonsterSpawnInterval);
}

void UDungeonManager::EnterDungeon(const int32 InDungeonID)
{
	UTableManager* TableMgr = GetGameInstance()->GetSubsystem<UTableManager>();
	if (!TableMgr) return;

	const auto* DungeonTableData = TableMgr->GetDungeonTableData(InDungeonID);
	if (!DungeonTableData) return;

	TeleportPlayer(DungeonTableData->SpawnLocation);
	
	InitDungeonSetting();
}

void UDungeonManager::ExitDungeon()
{
	const FVector TownLocation = FVector(1780.f, -1153.f, 302.f);
	TeleportPlayer(TownLocation);
	
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ExitTimerHandle);
	
	for (auto& Monster : MonsterList)
	{
		if (!Monster)
		{
			continue;
		}
		
		Monster->OnLapCountChanged.RemoveAll(this);
		Monster->OnMonsterDead.RemoveAll(this);
		Monster->OnMonsterWin.RemoveAll(this);
		Monster->Destroy();
	}
	
	MonsterList.Empty();
	SpawnedCount = 0;
	CachedPatrolPathActor = nullptr;
}

void UDungeonManager::TeleportPlayer(const FVector& InLocation) const
{
	// Todo : 이펙트 추가하면 이펙트가 끝나는 시점에 호출.
	
	const UWorld* World = GetGameInstance()->GetWorld();
	if (!World) return;

	APawn* PlayerPawn = World->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) return;
	
	AWarLegendCharacter* MyCharacter = Cast<AWarLegendCharacter>(PlayerPawn);
	if (!MyCharacter) return;

	MyCharacter->ChangeCamera(ECameraMode::Battle);
	MyCharacter->SetActorLocation(InLocation);
}

AWLPatrolPathActor* UDungeonManager::GetPatrolPath()
{
	AWLPatrolPathActor* PatrolPath = nullptr;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWLPatrolPathActor::StaticClass(), FoundActors);
	if (!FoundActors.IsEmpty())
	{
		PatrolPath = Cast<AWLPatrolPathActor>(FoundActors[0]);
	}
	
	return PatrolPath;
}

void UDungeonManager::SpawnMonster()
{
	if (SpawnedCount >= Constant::MonsterSpawnNum)
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}
	
	if (!CachedPatrolPathActor)
	{
		CachedPatrolPathActor = GetPatrolPath();
		if (!CachedPatrolPathActor)
		{
			return;
		}
	}
	
	const FVector SpawnLocation = CachedPatrolPathActor->GetWaypointWorldLocation(0);
 
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.bDeferConstruction = true;  // 생성만 하고 빙의 나중에
 
	auto* NewMonster = GetWorld()->SpawnActor<AMonster>(MonsterClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	if (!NewMonster) return;
 
	NewMonster->SetPatrolPath(CachedPatrolPathActor);
	NewMonster->FinishSpawning(FTransform(FRotator::ZeroRotator, SpawnLocation));	// 빙의 완료하고 바로 이동할수 있게
	
	NewMonster->OnLapCountChanged.AddUObject(this, &UDungeonManager::HandleLapCountChanged);
	NewMonster->OnMonsterDead.AddUObject(this, &UDungeonManager::HandleMonsterDead);
	NewMonster->OnMonsterWin.AddUObject(this, &UDungeonManager::HandleMonsterWin);
 
	MonsterList.Add(NewMonster);
	++SpawnedCount;
 
	OnMonsterSpawned.Broadcast(NewMonster, MonsterList.Num());
}
 
void UDungeonManager::HandleLapCountChanged(AMonster* InMonster, const int32 InNewLapCount)
{
	if (!InMonster)
	{
		return;
	}
	
	OnMonsterLapChanged.Broadcast(InMonster, InNewLapCount);
}
 
void UDungeonManager::HandleMonsterDead(AMonster* InMonster)
{
	if (!InMonster)
	{
		return;
	}
 
	MonsterList.Remove(InMonster);
	OnMonsterRemoved.Broadcast(InMonster);
	InMonster->Destroy();
}
 
void UDungeonManager::HandleMonsterWin()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ExitTimerHandle);
	OnDungeonFailed.Broadcast();
	
	GetWorld()->GetTimerManager().SetTimer(ExitTimerHandle, this, &UDungeonManager::ExitDungeon, Constant::DungeonExitTime, false);
}
