// ABD


#include "Item/C_StoneBase.h"
#include "Creature/C_Player.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"
#include "C_GameplayTags.h"
void AC_StoneBase::Consume(UC_CreatureAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	);

	BP_OnStoneConsumed();
}
void AC_StoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AC_Player* OverlappedPlayerCharacter = Cast<AC_Player>(OtherActor))
	{
		OverlappedPlayerCharacter->GetCreatureAbilitySystemComponent()->TryActivateAbilityByTag(BD_GamePlayTags::Player_Ability_PickUp_Stone);


	}
}
