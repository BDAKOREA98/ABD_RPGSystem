// ABD

#pragma once

#include "CoreMinimal.h"
#include "Creature/C_Creature.h"
#include "C_Enemy.generated.h"


class UBoxComponent;
class UC_EnemyCombatComponent;
class UC_EnemyUIComponent;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API AC_Enemy : public AC_Creature
{
	GENERATED_BODY()
	
public:
	AC_Enemy();

	//Begin IPawnCombatInterface Interface
	virtual UC_PawnCombatComponent* GetPawnCombatComponent() const override;
	//End IPawnCombatInterface Interface

	//Begin IPawnUIComponent Interface
	virtual UC_PawnUIComponent* GetPawnUIComponent()  const override;
	virtual UC_EnemyUIComponent* GetEnemyUIComponent() const override;
	//End IPawnUIComponent Interface

protected:
	virtual void BeginPlay() override;

	//begin APwan interfece
	virtual void PossessedBy(AController* NewController) override;
	//end APwan interfece
	//begin UObject interfece
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
	//end uObject interfece
#endif
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UC_EnemyCombatComponent* EnemyCombatComponent;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName LeftHandCollisionBoxAttachBoneName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	FName RightHandCollisionBoxAttachBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UBoxComponent* LeftHandCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UBoxComponent* RightHandCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UC_EnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;


	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void InitEnemyStartUpData();

public:

	FORCEINLINE UC_EnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
	FORCEINLINE UBoxComponent* GetLeftHandCollisionBox() const { return LeftHandCollisionBox; }
	FORCEINLINE UBoxComponent* GetRightHandCollisionBox() const { return RightHandCollisionBox; }

};
