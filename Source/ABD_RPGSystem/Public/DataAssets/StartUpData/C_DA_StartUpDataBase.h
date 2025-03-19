// ABD

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "C_DA_StartUpDataBase.generated.h"

class UC_CreatureGameplayAbility;
class UC_CreatureAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_DA_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:

	virtual void GiveToAbilitySystemComponent(UC_CreatureAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray <TSubclassOf< UC_CreatureGameplayAbility> > ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray <TSubclassOf< UC_CreatureGameplayAbility> > ReactivateAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf< UGameplayEffect> > StartUpGameplayEffect;


	void GrantAbilities(const TArray <TSubclassOf< UC_CreatureGameplayAbility> >& InAbilitiesToGive, UC_CreatureAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

};
