// ABD

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_WidgetBase.generated.h"

class UC_PlayerUIComponent;
/**
 * 
 */
UCLASS()
class ABD_RPGSYSTEM_API UC_WidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnOnwingPlayerUIComponentInitialized"))

	void BP_OnOnwingPlayerUIComponentInitialized(UC_PlayerUIComponent* OwningPlayerUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnOnwingEnemyUIComponentInitialized"))

	void BP_OnOnwingEnemyUIComponentInitialized(UC_EnemyUIComponent* OwningEnemyUIComponent);

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreateWidget(AActor* OwningEnemyActor);


};
