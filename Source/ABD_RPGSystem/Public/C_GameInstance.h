// ABD

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagContainer.h"
#include "C_GameInstance.generated.h"


USTRUCT(BlueprintType)
struct FGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}

};

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	virtual void Init() override;
protected:

	virtual void OnPreLoadMap(const FString& MapName);
	virtual void OnDestinationWorldLoaded(UWorld* LoadedWorld);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FGameLevelSet> GameLevelSets;

public:
	UFUNCTION(BlueprintPure, meta = (GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;
};
