// ABD

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "C_DA_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FPlayerInputActionConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UInputAction* InputAction;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}


};
/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_DA_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (TitleProperty = "InputTag"))
	TArray<FPlayerInputActionConfig> NativeInputActions;

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (TitleProperty = "InputTag"))
	TArray<FPlayerInputActionConfig> AbilityInputActions;

};
