// ABD

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "C_MasterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_MasterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UC_MasterAnimInstance();

protected:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool DoesOwnerHaveTag(FGameplayTag TagToCheck) const;

};
