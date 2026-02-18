// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonTriggerActor.h"
#include "Character/WarLegendPlayerController.h"
#include "Components/BoxComponent.h"
#include "DataManager/UIManager.h"
#include "DataManager/UIManagerImpl.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACommonTriggerActor::ACommonTriggerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	// 메쉬는 지나갈 거면 충돌 끄거나 NoCollision 권장
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetCollisionObjectType(ECC_WorldDynamic);
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Trigger->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ACommonTriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (!Trigger)
	{
		return;
	}
	
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACommonTriggerActor::OnTriggerBegin);
}

void ACommonTriggerActor::OnTriggerBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 플레이어만 반응
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (OtherActor != PlayerPawn)
	{
		return;
	}
	
	SetTriggerAction();
}

void ACommonTriggerActor::SetTriggerAction()
{
	if (ActorHasTag(FName("Dungeon")))
	{
		OpenDungeonMenu();
	}
	else if (ActorHasTag(FName("Boss")))
	{
		MoveToBossPosition();
	}
}

void ACommonTriggerActor::OpenDungeonMenu()
{
	AWarLegendPlayerController* PlayerController =  Cast<AWarLegendPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PlayerController)
	{
		// 대안.
		PlayerController = Cast<AWarLegendPlayerController>(GetInstigatorController()); 
	}
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("[OpenDungeonMenu] PlayerController Null"));
		return;
	}
	const auto LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("[OpenDungeonMenu] LocalPlayer Null"));
		return;
	}
	
	const auto UIMgr = LocalPlayer->GetSubsystem<UIManager>()->MgrImpl;
	if (!UIMgr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[OpenDungeonMenu] UIMgr Null"));
		return;
	}
	
	UIMgr->ShowUI(TEXT("PopupDungeonMenu"));
}

void ACommonTriggerActor::MoveToBossPosition()
{
}

// Called every frame
void ACommonTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

