// ABD

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/C_DA_InputConfig.h"
#include "C_InputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_InputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	

public:

	template<class UserObject, typename CallbackFunc>

	void BindNativeInputAction(const UC_DA_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UC_DA_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc);


};

template<class UserObject, typename CallbackFunc>
inline void UC_InputComponent::BindNativeInputAction(const UC_DA_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{

	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}

}

template<class UserObject, typename CallbackFunc>
inline void UC_InputComponent::BindAbilityInputAction(const UC_DA_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));

	for (const FPlayerInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid())
		{
			continue;
		}
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, AbilityInputActionConfig.InputTag);
	}

};
