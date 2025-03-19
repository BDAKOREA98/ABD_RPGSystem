// ABD

#pragma once

#include "CoreMinimal.h"
#include "Component/Combat/C_PawnCombatComponent.h"
#include "C_EnemyCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_EnemyCombatComponent : public UC_PawnCombatComponent
{
	GENERATED_BODY()
public:

	virtual void OnHitTargetActor(AActor* HitActor) override;
protected:

	virtual void ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType) override;
};
