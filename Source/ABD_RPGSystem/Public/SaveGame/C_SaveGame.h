// ABD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Types/EnumTypes.h"
#include "C_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	EGameDifficulty SavedCurrentGameDifficulty;
};
