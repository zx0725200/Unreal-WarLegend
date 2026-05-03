#include "HeroAnimNotify.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "ETC/Define.h"

void UHeroAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	VALID_RETURN(MeshComp);
	
	AActor* MyOwner = MeshComp->GetOwner();
	VALID_RETURN(MyOwner);
	
	FGameplayEventData Payload;
	Payload.EventTag = EventTag;
	Payload.Instigator = MyOwner;
	
	// WaitGameplayEvent 어빌리티 태스크에게 전달.
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MyOwner, EventTag, Payload);
}
