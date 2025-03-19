// ABD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Types/EnumTypes.h"
#include "C_RPGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API AC_RPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AC_RPGGameMode();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Game Settings")
	EGameDifficulty CurrentGameDifficulty;

public:

	FORCEINLINE EGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
};
