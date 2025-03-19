// ABD

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "C_AbilityTask_WaitSpawnEnemies.generated.h"

class AC_Enemy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemiesDelegate, const TArray<AC_Enemy*>&, SpawnedEnemies);
/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_AbilityTask_WaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Creature|AbilityTasks", meta = (DisplayName = "Wait Gameplay Event And Spawn Enemies", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", NumToSpawn = "1", RandomSpawnRadius = "200"))
	static UC_AbilityTask_WaitSpawnEnemies* WaitSpawnEnemies(
		UGameplayAbility* OwningAbility,
		FGameplayTag EventTag,
		TSoftClassPtr<AC_Enemy> SoftEnemyClassToSpawn,
		int32 NumToSpawn,
		const FVector& SpawnOrigin,
		float RandomSpawnRadius

	);

	// Begin UGameplayTask Interface
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	// End UGameplayTask Interface

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate OnSpawnFinish;

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate DidNotSpawn;

private:

	FGameplayTag	CachedEventTag;
	TSoftClassPtr<AC_Enemy> CachedSoftEnemyClassToSpawn;
	int32		CachedNumToSpawn;
	FVector CachedSpawnOrigin;
	float CachedRandomSpawnRadius;

	FDelegateHandle DelegateHandle;

	void OnGameplayEventReceived(const FGameplayEventData* InPayload);
	void OnEnemyClassLoaded();
};
