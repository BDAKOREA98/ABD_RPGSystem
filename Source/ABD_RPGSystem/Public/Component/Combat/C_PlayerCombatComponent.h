// ABD

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/C_PawnCombatComponent.h"
#include "C_PlayerCombatComponent.generated.h"

class AC_PlayerWeapon;

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_PlayerCombatComponent : public UC_PawnCombatComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Creature|Combat")
	AC_PlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Creature|Combat")
	AC_PlayerWeapon* GetPlayerCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Creature|Combat")
	float GetPlayerCurrentEquippedWeaponDamageAtLevel(float InLevel) const;


	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;


};
