// ABD


#include "Types/StructTypes.h"
#include "AbilitySystem/Abilities/C_PlayerGameplayAbility.h"


bool FPlayerAbilitySet::IsValid() const
{
    return InputTag.IsValid() && AbilityToGrant;
}
