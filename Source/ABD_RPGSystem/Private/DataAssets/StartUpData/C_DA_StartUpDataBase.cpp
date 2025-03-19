// ABD


#include "DataAssets/StartUpData/C_DA_StartUpDataBase.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"
#include "AbilitySystem/C_CreatureGameplayAbility.h"
void UC_DA_StartUpDataBase::GiveToAbilitySystemComponent(UC_CreatureAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	check(InASCToGive);
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactivateAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffect.IsEmpty())
	{
		for (const TSubclassOf< UGameplayEffect>& EffectClass : StartUpGameplayEffect)
		{
			if (!EffectClass)
			{
				continue;
			}
			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();

			InASCToGive->ApplyGameplayEffectToSelf(

				EffectCDO,
				ApplyLevel,
				InASCToGive->MakeEffectContext()

			);
		}
	}
}

void UC_DA_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UC_CreatureGameplayAbility>>& InAbilitiesToGive, UC_CreatureAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UC_CreatureGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(Ability);

		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;



		InASCToGive->GiveAbility(AbilitySpec);

	}
}
