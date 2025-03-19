// ABD


#include "Weapon/C_PlayerWeapon.h"

void AC_PlayerWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
    GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AC_PlayerWeapon::GetGrantedAbilitySpecHandles() const
{
    return GrantedAbilitySpecHandles;
}
