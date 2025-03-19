// ABD

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/C_CreatureGameplayAbility.h"
#include "C_EnemyGameplayAbility.generated.h"

class AC_Enemy;
class UC_EnemyCombatComponent;

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_EnemyGameplayAbility : public UC_CreatureGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Creature|Ability")
	AC_Enemy* GetEnemyCharacterFromActorInfor();

	UFUNCTION(BlueprintPure, Category = "Creature|Ability")
	UC_EnemyCombatComponent* GetEnemyCombatComponentFromActorInfor();

	UFUNCTION(BlueprintPure, Category = "Creature|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);

private:

	TWeakObjectPtr<AC_Enemy> CachedEnemyCharacter;
};
