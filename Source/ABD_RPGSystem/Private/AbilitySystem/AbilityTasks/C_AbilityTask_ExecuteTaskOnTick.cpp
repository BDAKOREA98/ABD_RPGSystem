// ABD


#include "AbilitySystem/AbilityTasks/C_AbilityTask_ExecuteTaskOnTick.h"

UC_AbilityTask_ExecuteTaskOnTick::UC_AbilityTask_ExecuteTaskOnTick()
{
    bTickingTask = true;
}

UC_AbilityTask_ExecuteTaskOnTick* UC_AbilityTask_ExecuteTaskOnTick::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
    UC_AbilityTask_ExecuteTaskOnTick* Node = NewAbilityTask< UC_AbilityTask_ExecuteTaskOnTick>(OwningAbility);

    return Node;
}

void UC_AbilityTask_ExecuteTaskOnTick::TickTask(float DeltaTime)
{
    Super::TickTask(DeltaTime);

    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnAbilityTaskTick.Broadcast(DeltaTime);

    }
    else
    {
        EndTask();
    }
}
