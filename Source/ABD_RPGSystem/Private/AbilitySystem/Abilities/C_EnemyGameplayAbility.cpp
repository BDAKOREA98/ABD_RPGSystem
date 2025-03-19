// ABD


#include "AbilitySystem/Abilities/C_EnemyGameplayAbility.h"
#include "Creature/C_Enemy.h"
#include "Component/Combat/C_EnemyCombatComponent.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"
#include "C_GameplayTags.h"
AC_Enemy* UC_EnemyGameplayAbility::GetEnemyCharacterFromActorInfor()
{
    if (!CachedEnemyCharacter.IsValid())
    {
		CachedEnemyCharacter = Cast<AC_Enemy>(CurrentActorInfo->AvatarActor);
    }

    return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UC_EnemyCombatComponent* UC_EnemyGameplayAbility::GetEnemyCombatComponentFromActorInfor()
{
    return GetEnemyCharacterFromActorInfor()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UC_EnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
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
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);




	return EffectSpecHandle;
}
