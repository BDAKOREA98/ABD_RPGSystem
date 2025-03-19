// ABD


#include "C_GameInstance.h"
#include "MoviePlayer.h"

void UC_GameInstance::Init()
{
	Super::Init();


	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnDestinationWorldLoaded);

}

void UC_GameInstance::OnPreLoadMap(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 5.f;
	LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void UC_GameInstance::OnDestinationWorldLoaded(UWorld* LoadedWorld)
{
	GetMoviePlayer()->StopMovie();
}

TSoftObjectPtr<UWorld> UC_GameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	for (const FGameLevelSet& GameLevelSet : GameLevelSets)
	{
		if (!GameLevelSet.IsValid())
		{
			continue;
		}
		if (GameLevelSet.LevelTag == InTag)
		{
			return GameLevelSet.Level;
		}
	}

	return TSoftObjectPtr<UWorld>();
}
