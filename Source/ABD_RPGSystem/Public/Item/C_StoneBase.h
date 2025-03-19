// ABD

#pragma once

#include "CoreMinimal.h"
#include "Item/C_PickUpBase.h"
#include "C_StoneBase.generated.h"

class UC_CreatureAbilitySystemComponent;
class UGameplayEffect;

/**
/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API AC_StoneBase : public AC_PickUpBase
{
	GENERATED_BODY()

public:
	void Consume(UC_CreatureAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);


protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Stone Consumed"))
	void BP_OnStoneConsumed();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};
