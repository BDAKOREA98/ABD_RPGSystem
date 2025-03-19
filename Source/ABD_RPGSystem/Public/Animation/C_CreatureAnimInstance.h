// ABD

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_MasterAnimInstance.h"
#include "C_CreatureAnimInstance.generated.h"


class AC_Creature;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_CreatureAnimInstance : public UC_MasterAnimInstance
{
	GENERATED_BODY()
	

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	void NormalizeDirection();


protected:

	UPROPERTY()
	AC_Creature* OwnerCreature;

	UPROPERTY()
	UCharacterMovementComponent* OwnerMovement;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AnimData|LocomotionData")
	float LocomotionDirection;

};
