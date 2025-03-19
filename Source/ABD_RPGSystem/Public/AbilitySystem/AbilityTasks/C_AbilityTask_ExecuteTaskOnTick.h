// ABD

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "C_AbilityTask_ExecuteTaskOnTick.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickDelegate, float, DelataTime);


/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_AbilityTask_ExecuteTaskOnTick : public UAbilityTask
{
	GENERATED_BODY()


public:

	UC_AbilityTask_ExecuteTaskOnTick();

	UFUNCTION(BlueprintCallable, Category = "Creature|AbilityTasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UC_AbilityTask_ExecuteTaskOnTick* ExecuteTaskOnTick(UGameplayAbility* OwningAbility);

	// Begin UGameplayTask Interface
	virtual void TickTask(float DeltaTime) override;
	// End UGameplayTask Interface

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskTickDelegate OnAbilityTaskTick;
	
};
