// ABD

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_PawnCombatInterface.generated.h"

class UC_PawnCombatComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UC_PawnCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ABD_RPGSYSTEM_API IC_PawnCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UC_PawnCombatComponent* GetPawnCombatComponent() const = 0;
};
