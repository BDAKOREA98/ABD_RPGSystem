// ABD


#include "DataAssets/StartUpData/C_DA_PlayerStartUpData.h"
#include "Types/StructTypes.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/C_PlayerGameplayAbility.h"

void UC_DA_PlayerStartUpData::GiveToAbilitySystemComponent(UC_CreatureAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{

	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);



	for (const FPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);


		InASCToGive->GiveAbility(AbilitySpec);


	}

}
