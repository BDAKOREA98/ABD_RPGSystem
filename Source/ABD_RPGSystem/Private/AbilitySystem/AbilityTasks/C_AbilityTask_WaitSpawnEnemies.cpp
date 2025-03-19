// ABD


#include "AbilitySystem/AbilityTasks/C_AbilityTask_WaitSpawnEnemies.h"
#include "AbilitySystemComponent.h"
#include "Engine/AssetManager.h"
#include "NavigationSystem.h"
#include "Creature/C_Enemy.h"

#include "MyDebugHelper.h"
UC_AbilityTask_WaitSpawnEnemies* UC_AbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag, TSoftClassPtr<AC_Enemy> SoftEnemyClassToSpawn, int32 NumToSpawn, const FVector& SpawnOrigin, float RandomSpawnRadius)
{

    UC_AbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<UC_AbilityTask_WaitSpawnEnemies>(OwningAbility);

    Node->CachedEventTag = EventTag;
    Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
    Node->CachedNumToSpawn = NumToSpawn;
    Node->CachedSpawnOrigin = SpawnOrigin;
    Node->CachedRandomSpawnRadius = RandomSpawnRadius;




    return Node;
}

void UC_AbilityTask_WaitSpawnEnemies::Activate()
{
    FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

    DelegateHandle = Delegate.AddUObject(this, &ThisClass::OnGameplayEventReceived);


}

void UC_AbilityTask_WaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
    FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

    Delegate.Remove(DelegateHandle);

    Super::OnDestroy(bInOwnerFinished);

}

void UC_AbilityTask_WaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* InPayload)
{
    if (ensure(!CachedSoftEnemyClassToSpawn.IsNull()))
    {
        UAssetManager::Get().GetStreamableManager().RequestAsyncLoad
        (
            CachedSoftEnemyClassToSpawn.ToSoftObjectPath(),
            FStreamableDelegate::CreateUObject(this, &ThisClass::OnEnemyClassLoaded)

        );
    }
    else
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            DidNotSpawn.Broadcast(TArray<AC_Enemy*>());
        }
        EndTask();
    }



}

void UC_AbilityTask_WaitSpawnEnemies::OnEnemyClassLoaded()
{
    UClass* LoadedClass = CachedSoftEnemyClassToSpawn.Get();
    UWorld* World = GetWorld();

    if (!LoadedClass || !World)
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            DidNotSpawn.Broadcast(TArray<AC_Enemy*>());
        }

        EndTask();

        return;
    }

    TArray<AC_Enemy*> SpawnedEnemies;

    FActorSpawnParameters SpawnParam;
    SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


    for (int32 i = 0; i < CachedNumToSpawn; i++)
    {
        FVector RandomLocation;
        UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, CachedSpawnOrigin, RandomLocation, CachedRandomSpawnRadius);

        RandomLocation += FVector(0.f, 0.f, 150.f);

        const FRotator SpawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

        AC_Enemy* SpawnedEnemy = World->SpawnActor<AC_Enemy>(LoadedClass, RandomLocation, SpawnFacingRotation, SpawnParam);

        if (SpawnedEnemy)
        {
            SpawnedEnemies.Add(SpawnedEnemy);
        }

    }

    if (ShouldBroadcastAbilityTaskDelegates())
    {
        if (!SpawnedEnemies.IsEmpty())
        {
            OnSpawnFinish.Broadcast(SpawnedEnemies);
        }
        else
        {
            DidNotSpawn.Broadcast(TArray<AC_Enemy*>());

        }

    }

    EndTask();
}
