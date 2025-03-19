// ABD


#include "Component/Combat/C_EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "C_GameplayTags.h"
#include "C_FunctionLibrary.h"
#include "Creature/C_Enemy.h"
#include "Components/BoxComponent.h"


#include "MyDebugHelper.h"
void UC_EnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;

	}

	OverlappedActors.AddUnique(HitActor);

	//TODO :: Implement block check

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UC_FunctionLibrary::NativeDoesActorHaveTag(HitActor, BD_GamePlayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UC_FunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), BD_GamePlayTags::Enemy_Status_Unblockable);



	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UC_FunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;



	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			BD_GamePlayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			BD_GamePlayTags::Shared_Event_MeleeHit,
			EventData
		);
	}

}

void UC_EnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AC_Enemy* OwningEnemy = GetOwningPawn<AC_Enemy>();

	check(OwningEnemy);

	UBoxComponent* LeftHand = OwningEnemy->GetLeftHandCollisionBox();
	UBoxComponent* RightHand = OwningEnemy->GetRightHandCollisionBox();

	check(LeftHand && RightHand);

	switch (ToggleDamageType)
	{

	case EToggleDamageType::LeftHand:
		LeftHand->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHand->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();

	}

}
