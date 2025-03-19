// ABD

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_MasterAnimInstance.h"
#include "C_PlayerLinkedLayer.generated.h"


class UC_PlayerAnimInstance;


/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_PlayerLinkedLayer : public UC_MasterAnimInstance
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UC_PlayerAnimInstance* GetPlayerAnimInstance() const;

};
