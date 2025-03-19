// ABD


#include "Animation/C_CreatureAnimInstance.h"
#include "Creature/C_Creature.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "KismetAnimationLibrary.h"

void UC_CreatureAnimInstance::NativeInitializeAnimation()
{
	OwnerCreature = Cast<AC_Creature>(TryGetPawnOwner());
	if (OwnerCreature)
	{
		OwnerMovement = OwnerCreature->GetCharacterMovement();

	}

}

void UC_CreatureAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwnerCreature || !OwnerMovement)
	{
		return;
	}

	GroundSpeed = OwnerCreature->GetVelocity().Size2D();

	bHasAcceleration = OwnerMovement->GetCurrentAcceleration().SizeSquared2D() > 0.0f;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwnerCreature->GetVelocity(), OwnerCreature->GetActorRotation());

	NormalizeDirection();
}

void UC_CreatureAnimInstance::NormalizeDirection()
{
	if (LocomotionDirection > 180.0f)
	{
		LocomotionDirection -= 360.0f;
	}
	else if (LocomotionDirection < -180.0f)
	{
		LocomotionDirection += 360.0f;
	}
}
