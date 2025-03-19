// ABD

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_CreatureAnimInstance.h"
#include "C_PlayerAnimInstance.generated.h"

class AC_Player;

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_PlayerAnimInstance : public UC_CreatureAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;




protected:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AnimData|Refrences")
	AC_Player* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 2.0f;

	float IdleElpasedTime;
};
