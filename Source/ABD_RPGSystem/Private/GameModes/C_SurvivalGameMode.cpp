// ABD


#include "GameModes/C_SurvivalGameMode.h"
#include "Engine/AssetManager.h"
#include "Creature/C_Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "NavigationSystem.h"
#include "C_FunctionLibrary.h"

#include "MyDebugHelper.h"

void AC_SurvivalGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	EGameDifficulty SaveGameDifficulty;
	if (UC_FunctionLibrary::TryLoadSavedGameDifficulty(SaveGameDifficulty))
	{

		CurrentGameDifficulty = SaveGameDifficulty;

	}
}

void AC_SurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid datat table in survial game mode blueprint"));

	SetCurrentSurvialGameModeState(ESurvialGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();

	PreLoadNextWaveEnemies();

}

void AC_SurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentSurvialGameModeState == ESurvialGameModeState::WaitSpawnNewWave)
	{
		TimePassedSinceStart += DeltaTime;
		if (TimePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			TimePassedSinceStart = 0.f;
			SetCurrentSurvialGameModeState(ESurvialGameModeState::SpawningNewWave);
		}
	}

	if (CurrentSurvialGameModeState == ESurvialGameModeState::SpawningNewWave)
	{
		TimePassedSinceStart += DeltaTime;
		if (TimePassedSinceStart >= SpawnEnemiesDelayTime)
		{
			CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();

			TimePassedSinceStart = 0.f;

			SetCurrentSurvialGameModeState(ESurvialGameModeState::InProgress);

		}
	}

	if (CurrentSurvialGameModeState == ESurvialGameModeState::WaveCompleted)
	{
		TimePassedSinceStart += DeltaTime;
		if (TimePassedSinceStart >= WaveCompleteWaitTime)
		{
			TimePassedSinceStart = 0.f;
			CurrentWaveCount++;
			if (HasFinishedAllWaves())
			{
				SetCurrentSurvialGameModeState(ESurvialGameModeState::AllWavesDone);

			}
			else
			{
				SetCurrentSurvialGameModeState(ESurvialGameModeState::WaitSpawnNewWave);
				PreLoadNextWaveEnemies();
			}

		}

	}

}

void AC_SurvivalGameMode::SetCurrentSurvialGameModeState(ESurvialGameModeState InState)
{
	CurrentSurvialGameModeState = InState;

	OnSurvialGameModeStateChanged.Broadcast(CurrentSurvialGameModeState);



}

bool AC_SurvivalGameMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}

void AC_SurvivalGameMode::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves())
	{
		return;
	}

	PreLoadedEnemyClassMap.Empty();


	for (const FEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull())
		{
			continue;
		}
		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda(
				[SpawnerInfo, this]()
				{
					if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
					{
						PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);



					}
				}
			)
		);

	}


}

FEnemyWaveSpawnerTableRow* AC_SurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));

	FEnemyWaveSpawnerTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow< FEnemyWaveSpawnerTableRow>(RowName, FString());

	checkf(FoundRow, TEXT("Could not find valid row under the name %s in the data table"), *RowName.ToString());

	return FoundRow;
}

int32 AC_SurvivalGameMode::TrySpawnWaveEnemies()
{
	if (TargetPointArray.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPointArray);
	}

	checkf(!TargetPointArray.IsEmpty(), TEXT("No calid target point found in level : %s for spawning eneies"), *GetWorld()->GetName());


	uint32 EnemiesSpawnedThisTime = 0;

	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (const FEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerDefinitions)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull())
		{
			continue;
		}
		const int32 NumToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount, SpawnerInfo.MaxPerSpawnCount);

		UClass* LoadedEnemyClass = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);

		for (int32 i = 0; i < NumToSpawn; i++)
		{
			const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPointArray.Num() - 1);
			const FVector SpawnOrigin = TargetPointArray[RandomTargetPointIndex]->GetActorLocation();
			const FRotator SpawnRotation = TargetPointArray[RandomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();

			FVector RandomLocation;
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnOrigin, RandomLocation, 400.0f);

			RandomLocation += FVector(0.f, 0.f, 150.f);

			AC_Enemy* SpawnedEnemy = GetWorld()->SpawnActor<AC_Enemy>(LoadedEnemyClass, RandomLocation, SpawnRotation, SpawnParam);

			if (SpawnedEnemy)
			{
				SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);

				EnemiesSpawnedThisTime++;
				TotalSpawnedEnemiesThisWaveCounter++;
			}

			if (!ShouldKeepSpawnEnemies())
			{
				return EnemiesSpawnedThisTime;
			}

		}

	}



	return EnemiesSpawnedThisTime;

}

bool AC_SurvivalGameMode::ShouldKeepSpawnEnemies() const
{
	return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}

void AC_SurvivalGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
	CurrentSpawnedEnemiesCounter--;


	if (ShouldKeepSpawnEnemies())
	{
		CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
	}
	else if (CurrentSpawnedEnemiesCounter == 0)
	{
		TotalSpawnedEnemiesThisWaveCounter = 0;
		CurrentSpawnedEnemiesCounter = 0;

		SetCurrentSurvialGameModeState(ESurvialGameModeState::WaveCompleted);
	};


}

void AC_SurvivalGameMode::RegisterSpawnedEnemies(const TArray<AC_Enemy*>& InEnemiesToRegister)
{
	for (AC_Enemy* SpawnedEnemy : InEnemiesToRegister)
	{
		if (SpawnedEnemy)
		{
			CurrentSpawnedEnemiesCounter++;

			SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
		}


	}
}
