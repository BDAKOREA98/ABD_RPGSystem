// ABD


#include "Component/UI/C_EnemyUIComponent.h"
#include "Widget/C_WidgetBase.h"
void UC_EnemyUIComponent::RegisterEnemyDrawWidget(UC_WidgetBase* InWidgetToRegister)
{
	EnemyDrawWidgets.Add(InWidgetToRegister);
}

void UC_EnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawWidgets.IsEmpty())
	{
		return;
	}
	for (UC_WidgetBase* DrawnWidget : EnemyDrawWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}

	EnemyDrawWidgets.Empty();
}
