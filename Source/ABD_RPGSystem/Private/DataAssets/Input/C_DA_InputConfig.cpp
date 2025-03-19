// ABD


#include "DataAssets/Input/C_DA_InputConfig.h"

UInputAction* UC_DA_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FPlayerInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
}
