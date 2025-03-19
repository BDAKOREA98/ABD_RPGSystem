// ABD

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/C_CreatureGameplayAbility.h"
#include "C_PlayerGameplayAbility.generated.h"


class AC_Player;
class AC_PlayerController;


/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_PlayerGameplayAbility : public UC_CreatureGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Creature|Ability")
	AC_Player* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Creature|Ability")
	AC_PlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Creature|Ability")
	UC_PlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Creature|Ability")
	UC_PlayerUIComponent* GetPlayerUIComponentActorInfo();


	UFUNCTION(BlueprintPure, Category = "Creature|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

	UFUNCTION(BlueprintCallable, Category = "Creature|Ability")
	bool GetAbilityRemaningCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemaningCooldownTime);

private:

	TWeakObjectPtr<AC_Player> CachedPlayerCharacter;
	TWeakObjectPtr<AC_PlayerController> CachedPlayerController;
};
