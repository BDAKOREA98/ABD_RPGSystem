// ABD


#include "AbilitySystem/C_CreatureGameplayAbility.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"
#include "Component/Combat/C_PawnCombatComponent.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "C_FunctionLibrary.h"
#include "C_GameplayTags.h"

void UC_CreatureGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (AbilityActivationPolicy == ECreatureAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);

		}
	}
}

void UC_CreatureGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == ECreatureAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);

		}
	}
}

UC_PawnCombatComponent* UC_CreatureGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UC_PawnCombatComponent>();

}

UC_CreatureAbilitySystemComponent* UC_CreatureGameplayAbility::GetCreatureAbilitySystemComponentFromActorInfo() const
{
	return Cast<UC_CreatureAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);

}

FActiveGameplayEffectHandle UC_CreatureGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());


	return GetCreatureAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC
	);
}

FActiveGameplayEffectHandle UC_CreatureGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ECreatureSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle  ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? ECreatureSuccessType::Succesful : ECreatureSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}

void UC_CreatureGameplayAbility::ApplyGameplayEffectSpecHandleToHitResult(const FGameplayEffectSpecHandle& InSpecHandle, const TArray<FHitResult>& InHitResult)
{
	if (InHitResult.IsEmpty())
	{
		return;
	}
	APawn* OwningPawn = CastChecked<APawn>(GetAvatarActorFromActorInfo());

	for (const FHitResult& Hit : InHitResult)
	{
		if (APawn* HitPawn = Cast<APawn>(Hit.GetActor()))
		{
			if (UC_FunctionLibrary::IsTargetPawnHostile(OwningPawn, HitPawn))
			{
				FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(HitPawn, InSpecHandle);

				if (ActiveGameplayEffectHandle.WasSuccessfullyApplied())
				{
					FGameplayEventData Data;
					Data.Instigator = OwningPawn;
					Data.Target = HitPawn;

					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
						HitPawn,
						BD_GamePlayTags::Shared_Event_HitReact,
						Data
					);
				}
			}

		}
	}
}
