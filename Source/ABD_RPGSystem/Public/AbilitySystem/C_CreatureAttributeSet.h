// ABD

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"
#include "C_CreatureAttributeSet.generated.h"

class IC_PawnUIInterface;

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)



/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_CreatureAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UC_CreatureAttributeSet();
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UC_CreatureAttributeSet, CurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UC_CreatureAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UC_CreatureAttributeSet, CurrentRage);

	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UC_CreatureAttributeSet, MaxRage);


	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UC_CreatureAttributeSet, AttackPower);

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefencePower;
	ATTRIBUTE_ACCESSORS(UC_CreatureAttributeSet, DefencePower);


	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UC_CreatureAttributeSet, DamageTaken);

private:

	TWeakInterfacePtr<IC_PawnUIInterface> CachedPawnUIInterface;
	
};
