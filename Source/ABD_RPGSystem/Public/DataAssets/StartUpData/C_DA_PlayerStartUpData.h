// ABD

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/C_DA_StartUpDataBase.h"
#include "Types/StructTypes.h"
#include "GameplayTagContainer.h"
#include "C_DA_PlayerStartUpData.generated.h"


class UC_CreatureAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_DA_PlayerStartUpData : public UC_DA_StartUpDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UC_CreatureAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FPlayerAbilitySet> PlayerStartUpAbilitySets;

};
