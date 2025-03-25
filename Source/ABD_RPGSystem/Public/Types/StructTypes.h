// ABD

#pragma once


#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "StructTypes.generated.h"

/**
 * 
 */

class UC_PlayerLinkedLayer;
class UC_CreatureGameplayAbility;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UC_CreatureGameplayAbility> AbilityToGrant;

	bool IsValid() const;

};
USTRUCT(BlueprintType)
struct FPlayerSpecialAbilitySet : public FPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (Categories = "Player.Cooldown"))
	TSoftObjectPtr<UMaterialInterface> SoftAbilityIconMaterial;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag AbilityCooldownTag;





};



USTRUCT(BlueprintType)
struct FPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf< UC_PlayerLinkedLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FPlayerAbilitySet> DefaultWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FPlayerSpecialAbilitySet> DefaultSpecialWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)

	FScalableFloat WeaponBaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;

};