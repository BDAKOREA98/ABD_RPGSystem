// ABD


#include "AbilitySystem/Abilities/C_Player_PickUpStone_GA.h"
#include "Creature/C_Player.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Item/C_StoneBase.h"
#include "Component/UI/C_PlayerUIComponent.h"

void UC_Player_PickUpStone_GA::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GetPlayerUIComponentActorInfo()->OnStoneInteracted.Broadcast(true);


	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UC_Player_PickUpStone_GA::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetPlayerUIComponentActorInfo()->OnStoneInteracted.Broadcast(false);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UC_Player_PickUpStone_GA::CollectStones()
{
	CollectedStones.Empty();

	TArray<FHitResult> TraceHits;

	

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + GetPlayerCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		GetPlayerCharacterFromActorInfo()->GetActorUpVector().ToOrientationRotator(),
		StoneTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& TraceHit : TraceHits)
	{
		if (AC_StoneBase* FoundStone = Cast<AC_StoneBase>(TraceHit.GetActor()))
		{
			CollectedStones.AddUnique(FoundStone);
		}
	}

	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}

}

void UC_Player_PickUpStone_GA::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	for (AC_StoneBase* CollectedStone : CollectedStones)
	{
		if (CollectedStone)
		{
			CollectedStone->Consume(GetCreatureAbilitySystemComponentFromActorInfo(), GetAbilityLevel());

		}
	}

}
