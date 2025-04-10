// ABD


#include "Creature/C_Creature.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"
#include "AbilitySystem/C_CreatureAttributeSet.h"
#include "MotionWarpingComponent.h"
// Sets default values
AC_Creature::AC_Creature()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;



	CreatureAbilityComponent = CreateDefaultSubobject<UC_CreatureAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	CreatureAttributeSet = CreateDefaultSubobject<UC_CreatureAttributeSet>(TEXT("AttributeSet"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

}

UAbilitySystemComponent* AC_Creature::GetAbilitySystemComponent() const
{
	return GetCreatureAbilitySystemComponent();
}

UC_PawnCombatComponent* AC_Creature::GetPawnCombatComponent() const
{
	return nullptr;
}

UC_PawnUIComponent* AC_Creature::GetPawnUIComponent() const
{
	return nullptr;
}

void AC_Creature::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (CreatureAbilityComponent)
	{
		CreatureAbilityComponent->InitAbilityActorInfo(this, this);



		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());


	}
}
