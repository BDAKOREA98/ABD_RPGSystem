// ABD


#include "Widget/C_WidgetBase.h"
#include "Interface/C_PawnUIInterface.h"
#include "Component/UI/C_PlayerUIComponent.h"
#include "Component/UI/C_EnemyUIComponent.h"

void UC_WidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IC_PawnUIInterface* PawnUIInterface = Cast<IC_PawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UC_PlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOnwingHeroUIComponentInitialized(PlayerUIComponent);
		}
	}
}


void UC_WidgetBase::InitEnemyCreateWidget(AActor* OwningEnemyActor)
{
	if (IC_PawnUIInterface* PawnUIInterface = Cast<IC_PawnUIInterface>(OwningEnemyActor))
	{
		UC_EnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

		checkf(EnemyUIComponent, TEXT("Failed to extrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOnwingEnemyUIComponentInitialized(EnemyUIComponent);
	}
}

