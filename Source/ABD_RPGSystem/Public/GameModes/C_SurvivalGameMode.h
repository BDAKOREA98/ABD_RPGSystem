// ABD

#pragma once

#include "CoreMinimal.h"
#include "GameModes/C_RPGGameMode.h"
#include "C_SurvivalGameMode.generated.h"
class AC_Enemy;

UENUM(BlueprintType)
enum class ESurvialGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied

};


USTRUCT(BlueprintType)
struct FEnemyWaveSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AC_Enemy> SoftEnemyClassToSpawn;

	UPROPERTY(EditAnywhere)
	int32 MinPerSpawnCount = 1;


	UPROPERTY(EditAnywhere)
	int32 MaxPerSpawnCount = 1;

};

USTRUCT(BlueprintType)
struct FEnemyWaveSpawnerTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray< FEnemyWaveSpawnerInfo> EnemyWaveSpawnerDefinitions;

	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpawnThisWave = 1;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvialGameModeStateChangeDelegate, ESurvialGameModeState, CurrentState);

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API AC_SurvivalGameMode : public AC_RPGGameMode
{
	GENERATED_BODY()

protected:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	void SetCurrentSurvialGameModeState(ESurvialGameModeState InState);
	bool HasFinishedAllWaves() const;
	void PreLoadNextWaveEnemies();
	FEnemyWaveSpawnerTableRow* GetCurrentWaveSpawnerTableRow() const;
	int32 TrySpawnWaveEnemies();
	bool ShouldKeepSpawnEnemies() const;

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);


	UPROPERTY()
	ESurvialGameModeState CurrentSurvialGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvialGameModeStateChangeDelegate OnSurvialGameModeStateChanged;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	UDataTable* EnemyWaveSpawnerDataTable;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	int32 TotalWavesToSpawn;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	int32 CurrentWaveCount = 1;

	UPROPERTY()
	int32 CurrentSpawnedEnemiesCounter = 0;

	UPROPERTY()
	int32 TotalSpawnedEnemiesThisWaveCounter = 0;

	UPROPERTY()
	TArray<AActor*> TargetPointArray;

	UPROPERTY()
	float TimePassedSinceStart = 0.f;;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float SpawnNewWaveWaitTime = 5.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float SpawnEnemiesDelayTime = 2.f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "WaveDefinition", meta = (AllowPrivateAccess = "true"))
	float WaveCompleteWaitTime = 5.f;

	UPROPERTY()
	TMap<TSoftClassPtr<AC_Enemy>, UClass* > PreLoadedEnemyClassMap;

public:
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnedEnemies(const TArray<AC_Enemy*>& InEnemiesToRegister);

	
};
