// ABD

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/C_DA_StartUpDataBase.h"
#include "C_DA_EnemyStartUpData.generated.h"


class UC_EnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_DA_EnemyStartUpData : public UC_DA_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UC_CreatureAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf < UC_EnemyGameplayAbility >> EnemyCombatAbilities;


};
