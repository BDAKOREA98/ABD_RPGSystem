// ABD

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "C_PawnUIInterface.generated.h"


class UC_PawnUIComponent;
class UC_PlayerUIComponent;
class UC_EnemyUIComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UC_PawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ABD_RPGSYSTEM_API IC_PawnUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UC_PawnUIComponent* GetPawnUIComponent() const = 0;
	virtual UC_PlayerUIComponent* GetPlayerUIComponent() const;
	virtual UC_EnemyUIComponent* GetEnemyUIComponent() const;

};
