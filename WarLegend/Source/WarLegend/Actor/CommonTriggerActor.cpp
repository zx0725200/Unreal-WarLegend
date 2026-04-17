// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonTriggerActor.h"

#include "UIManager.h"
#include "UIManagerImpl.h"
#include "Components/BoxComponent.h"
#include "Controller/WarLegendPlayerController.h"
#include "Kismet/GameplayStatics.h"


ACommonTriggerActor::ACommonTriggerActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	UStaticMeshComponent* Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Mesh;
	
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetCollisionObjectType(ECC_WorldDynamic);
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Trigger->SetGenerateOverlapEvents(true);
}

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
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (OtherActor != PlayerPawn)
	{
		return;
	}
	
	ExecuteTriggerByType();
}

void ACommonTriggerActor::ExecuteTriggerByType()
{
	if (!ActorHasTag(FName("Dungeon")))
	{
		return;
	}
	
	OpenDungeonMenu();
}

void ACommonTriggerActor::OpenDungeonMenu() const
{
	AWarLegendPlayerController* PlayerController =  Cast<AWarLegendPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!PlayerController)
	{
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


