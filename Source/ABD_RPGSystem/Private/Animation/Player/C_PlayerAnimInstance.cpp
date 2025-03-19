// ABD


#include "Animation/Player/C_PlayerAnimInstance.h"
#include "Creature/C_Player.h"

void UC_PlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwnerCreature)
	{
		OwnerCharacter = Cast<AC_Player>(OwnerCreature);
	}
}

void UC_PlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);


	if (bHasAcceleration)
	{
		IdleElpasedTime = 0.0f;
		bShouldEnterRelaxState = false;

	}
	else
	{
		IdleElpasedTime += DeltaSeconds;

		bShouldEnterRelaxState = (IdleElpasedTime >= EnterRelaxStateThreshold);


	}
}
