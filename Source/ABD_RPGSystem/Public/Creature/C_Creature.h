// ABD

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/C_PawnCombatInterface.h"
#include "Interface/C_PawnUIInterface.h"
#include "C_Creature.generated.h"

class UC_CreatureAbilitySystemComponent;
class UC_CreatureAttributeSet;
class UAbilitySystemComponent;
class UC_DA_StartUpDataBase;
class UMotionWarpingComponent;

UCLASS()
class ABD_RPGSYSTEM_API AC_Creature : public ACharacter, public IAbilitySystemInterface, public IC_PawnCombatInterface, public IC_PawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Creature();


	//Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//End IAbilitySystemInterface Interface

	//Begin IPawnCombatInterface Interface
	virtual UC_PawnCombatComponent* GetPawnCombatComponent() const override;
	//End IPawnCombatInterface Interface

	//Begin IPawnUIComponent Interface
	virtual UC_PawnUIComponent* GetPawnUIComponent()  const override;

	//End IPawnUIComponent Interface


protected:

protected:
	//begin APwan interfece
	virtual void PossessedBy(AController* NewController) override;
	//End APwan interfece
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UC_CreatureAbilitySystemComponent* CreatureAbilityComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UC_CreatureAttributeSet* CreatureAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UC_DA_StartUpDataBase> CharacterStartUpData;


public:
	FORCEINLINE UC_CreatureAbilitySystemComponent* GetWarriorAbilitySystemComponent() const { return CreatureAbilityComponent; }
	FORCEINLINE UC_CreatureAttributeSet* GetWarriorAttributeSet() const { return CreatureAttributeSet; }


};
