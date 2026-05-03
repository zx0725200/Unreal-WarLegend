#include "HeroFunctionLibrary.h"
#include "HeroCombatInterface.h"
#include "Component/PawnCombatComponentBase.h"


UPawnCombatComponentBase* UHeroFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IHeroCombatInterface* HeroCombatInterface = Cast<IHeroCombatInterface>(InActor))
	{
		return HeroCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponentBase* UHeroFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EWarriorConfirmType& OutConfirmType)
{
	UPawnCombatComponentBase* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	
	OutConfirmType = CombatComponent? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
	
	return CombatComponent;
}

UPawnCombatComponentBase* UHeroFunctionLibrary::GetPawnCombatComponentFromActor(AActor* InActor)
{
	UPawnCombatComponentBase* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	
	return CombatComponent;
}

