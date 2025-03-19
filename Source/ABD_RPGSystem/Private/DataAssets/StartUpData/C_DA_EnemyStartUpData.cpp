// ABD


#include "DataAssets/StartUpData/C_DA_EnemyStartUpData.h"
#include "AbilitySystem/Abilities/C_EnemyGameplayAbility.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"

void UC_DA_EnemyStartUpData::GiveToAbilitySystemComponent(UC_CreatureAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf < UC_EnemyGameplayAbility >& AbilityClass : EnemyCombatAbilities)
		{

			if (!AbilityClass)
			{
				continue;
			}
			FGameplayAbilitySpec AbilitySpec(AbilityClass);

			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InASCToGive->GiveAbility(AbilitySpec);




			float a = 1;

		}
	}

}
