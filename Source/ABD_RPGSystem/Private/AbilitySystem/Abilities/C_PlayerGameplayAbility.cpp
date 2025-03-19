// ABD


#include "AbilitySystem/Abilities/C_PlayerGameplayAbility.h"
#include "Creature/C_Player.h"
#include "Controller/C_PlayerController.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"
#include "C_GameplayTags.h"
AC_Player* UC_PlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedPlayerCharacter.IsValid())
	{
		CachedPlayerCharacter = Cast<AC_Player>(CurrentActorInfo->AvatarActor);
	}




	return CachedPlayerCharacter.IsValid() ? CachedPlayerCharacter.Get() : nullptr;
}

AC_PlayerController* UC_PlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedPlayerController.IsValid())
	{
		CachedPlayerController = Cast<AC_PlayerController>(CurrentActorInfo->PlayerController);

	}

	return CachedPlayerController.IsValid() ? CachedPlayerController.Get() : nullptr;
}

UC_PlayerCombatComponent* UC_PlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}

UC_PlayerUIComponent* UC_PlayerGameplayAbility::GetPlayerUIComponentActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerUIComponent();
}

FGameplayEffectSpecHandle UC_PlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetCreatureAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetCreatureAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		BD_GamePlayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage

	);


	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}





	return EffectSpecHandle;
}

bool UC_PlayerGameplayAbility::GetAbilityRemaningCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemaningCooldownTime)
{
	check(InCooldownTag.IsValid());
	FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());

	TArray<TPair<float, float>> TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

	if (!TimeRemainingAndDuration.IsEmpty())
	{
		RemaningCooldownTime = TimeRemainingAndDuration[0].Key;
		TotalCooldownTime = TimeRemainingAndDuration[0].Value;

	}

	return RemaningCooldownTime > 0.f;
}
