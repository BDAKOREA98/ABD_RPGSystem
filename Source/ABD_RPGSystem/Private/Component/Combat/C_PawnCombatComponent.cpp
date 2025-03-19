// ABD


#include "Component/Combat/C_PawnCombatComponent.h"
#include "Weapon/C_WeaponBase.h"
#include "Creature/C_Creature.h"
#include "Components/BoxComponent.h"

#include "MyDebugHelper.h"
void UC_PawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AC_WeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CraetureCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);


	CraetureCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);


	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

}

AC_WeaponBase* UC_PawnCombatComponent::GetCreatureCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CraetureCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AC_WeaponBase* const* FoundWeapon = CraetureCarriedWeaponMap.Find(InWeaponTagToGet))
		{

			return *FoundWeapon;
		}
	}


	return nullptr;
}

AC_WeaponBase* UC_PawnCombatComponent::GetCreatureCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}



	return GetCreatureCarriedWeaponByTag(CurrentEquippedWeaponTag);
}


void UC_PawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{

	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{

		ToggleCurrentEquippedWeaponCollision(bShouldEnable);

	}
	else
	{
		ToggleBodyCollisionBoxCollision(bShouldEnable, ToggleDamageType);
	}




}

void UC_PawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UC_PawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

void UC_PawnCombatComponent::ToggleCurrentEquippedWeaponCollision(bool bShouldEnable)
{
	AC_WeaponBase* WeaponToToggle = GetCreatureCurrentEquippedWeapon();

	check(WeaponToToggle);
	if (bShouldEnable)
	{
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);


	}
	else
	{
		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		OverlappedActors.Empty();


	}
}

void UC_PawnCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
}
