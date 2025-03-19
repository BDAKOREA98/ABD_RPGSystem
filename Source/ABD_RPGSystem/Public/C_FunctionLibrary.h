// ABD

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/EnumTypes.h"
#include "C_FunctionLibrary.generated.h"



class UC_CreatureAbilitySystemComponent;
class UC_PawnCombatComponent;
struct FScalableFloat;
class UC_GameInstance;



/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static UC_CreatureAbilitySystemComponent* NativeGetCreatureASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Creature|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Creature|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);



	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);


	UFUNCTION(BlueprintCallable, Category = "Creature|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ECreatureConfirmType& OutConfirmType);


	static UC_PawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Creature|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor"))
	static UC_PawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, ECreatureValidType& OutValidType);


	UFUNCTION(BlueprintPure, Category = "Creature|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "Creature|FunctionLibrary", meta = (CompactNodeTitle = "GetValue At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel);

	UFUNCTION(BlueprintPure, Category = "Creature|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDiffenece);

	UFUNCTION(BlueprintPure, Category = "Creature|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "Creature|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);


	UFUNCTION(BlueprintCallable, Category = "Creature|FunctionLibrary", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
		float& OutRemainingTime, ECreatureCountDownActionInput CountDownInput,
		UPARAM(DisplayName = "Output") ECreatureCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo);


	UFUNCTION(BlueprintPure, Category = "Creature|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static UC_GameInstance* GetGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Creature|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject, EInputMode InInputMode);

	UFUNCTION(BlueprintCallable, Category = "Creature|FunctionLibrary")
	static void SaveCurrentGameDifficulty(EGameDifficulty InDifficultyToSave);

	UFUNCTION(BlueprintCallable, Category = "Creature|FunctionLibrary")
	static bool TryLoadSavedGameDifficulty(EGameDifficulty& OutDifficultyToSave);
	
};
