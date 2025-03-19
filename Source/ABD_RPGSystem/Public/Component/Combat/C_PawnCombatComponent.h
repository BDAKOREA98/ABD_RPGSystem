// ABD

#pragma once

#include "CoreMinimal.h"
#include "Component/C_PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "C_PawnCombatComponent.generated.h"

class AC_WeaponBase;
UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};
/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_PawnCombatComponent : public UC_PawnExtensionComponentBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Creature|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AC_WeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Creature|Combat")
	AC_WeaponBase* GetCreatureCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;


	UPROPERTY(BlueprintReadWrite, Category = "Creature|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Creature|Combat")
	AC_WeaponBase* GetCreatureCurrentEquippedWeapon() const;


	UFUNCTION(BlueprintCallable, Category = "Creature|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);


	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:

	virtual void ToggleCurrentEquippedWeaponCollision(bool bShouldEnable);
	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);

	TArray<AActor*> OverlappedActors;


private:

	TMap<FGameplayTag, AC_WeaponBase*> CraetureCarriedWeaponMap;

};
