// ABD

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Types/EnumTypes.h"
#include "C_CreatureGameplayAbility.generated.h"

class UC_PawnCombatComponent;
class UC_CreatureAbilitySystemComponent;

UENUM(BlueprintType)
enum class ECreatureAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven

};

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_CreatureGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


protected:

	// Begin UGameplayAbility Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// Eegin UGameplayAbility Interface
	UPROPERTY(EditDefaultsOnly, Category = "CreatureAbility")
	ECreatureAbilityActivationPolicy AbilityActivationPolicy = ECreatureAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Creature|Ability")
	UC_PawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;


	UFUNCTION(BlueprintPure, Category = "Creature|Ability")
	UC_CreatureAbilitySystemComponent* GetCreatureAbilitySystemComponentFromActorInfo() const;
	


	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Creature|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))

	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ECreatureSuccessType& OutSuccessType);

	UFUNCTION(BlueprintCallable, Category = "Creature|Ability")
	void ApplyGameplayEffectSpecHandleToHitResult(const FGameplayEffectSpecHandle& InSpecHandle, const TArray<FHitResult>& InHitResult);

};
