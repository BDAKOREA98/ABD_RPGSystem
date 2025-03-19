// ABD


#include "Component/Combat/C_PlayerCombatComponent.h"
#include "Weapon/C_PlayerWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "C_GameplayTags.h"
#include "MyDebugHelper.h"

AC_PlayerWeapon* UC_PlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AC_PlayerWeapon>(GetCreatureCarriedWeaponByTag(InWeaponTag));
}

AC_PlayerWeapon* UC_PlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
    return Cast<AC_PlayerWeapon>(GetCreatureCurrentEquippedWeapon());
}

float UC_PlayerCombatComponent::GetPlayerCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
    return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UC_PlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (OverlappedActors.Contains(HitActor))
    {
        return;
    }

    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;




    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        BD_GamePlayTags::Shared_Event_MeleeHit,
        Data

    );

    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        BD_GamePlayTags::Player_Event_HitPause,
        FGameplayEventData()
    );

}

void UC_PlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}
