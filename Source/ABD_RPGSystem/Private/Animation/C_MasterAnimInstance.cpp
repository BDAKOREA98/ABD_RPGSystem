// ABD


#include "Animation/C_MasterAnimInstance.h"
#include "C_FunctionLibrary.h"
UC_MasterAnimInstance::UC_MasterAnimInstance()
{
}

bool UC_MasterAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UC_FunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
