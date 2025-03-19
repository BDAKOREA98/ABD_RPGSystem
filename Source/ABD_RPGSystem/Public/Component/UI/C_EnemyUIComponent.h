// ABD

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/C_PawnUIComponent.h"
#include "C_EnemyUIComponent.generated.h"
class UC_WidgetBase;
/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_EnemyUIComponent : public UC_PawnUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawWidget(UC_WidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();


private:
	TArray< UC_WidgetBase*> EnemyDrawWidgets;
};
