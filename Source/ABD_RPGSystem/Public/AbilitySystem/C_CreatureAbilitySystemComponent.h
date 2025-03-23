// ABD

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Types/StructTypes.h"
#include "C_CreatureAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_CreatureAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleassed(const FGameplayTag& InInputTag);


	UFUNCTION(BlueprintCallable, Category = "Craeture|Ability", meta = (ApplyLevel = "1"))
	void GrantPlayerWeaponAbilities(const TArray<FPlayerAbilitySet>& InDefaultWeaponAbilities, const TArray<FPlayerSpecialAbilitySet> InDefaultSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantAbilitySpecHandles);

	UFUNCTION(BlueprintCallable, Category = "Craeture|Ability")
	void RemoveGrantedPlayerWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "Craeture|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);

	
};
