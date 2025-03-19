// ABD

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_AIController.generated.h"
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API AC_AIController : public AAIController
{
	GENERATED_BODY()

public:
	AC_AIController(const FObjectInitializer& ObjectInitializer);

	// Begin IGenericTeamAgentInterface Interface.
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	// End IGenericTeamAgentInterface Interface.

protected:

	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* EnemyAISenseConfig_Sight;

	UFUNCTION()
	virtual void OnEnemyPercepationUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config")
	bool bEnableDetourCrowdAboidance = true;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAboidance", UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourCrowdAboidance"))
	float CollisionQueryRange = 600;

};
