// ABD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "C_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API AC_PlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AC_PlayerController();


	// Begin IGenericTeamAgentInterface Interface.
	virtual FGenericTeamId GetGenericTeamId() const override;
	// End IGenericTeamAgentInterface Interface.


private:
	FGenericTeamId PlayerTeamID;
};
