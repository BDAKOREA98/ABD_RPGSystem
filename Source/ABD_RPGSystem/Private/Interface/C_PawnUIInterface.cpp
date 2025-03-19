// ABD


#include "Interface/C_PawnUIInterface.h"

// Add default functionality here for any IC_PawnUIInterface functions that are not pure virtual.

UC_PlayerUIComponent* IC_PawnUIInterface::GetPlayerUIComponent() const
{
    return nullptr;
}

UC_EnemyUIComponent* IC_PawnUIInterface::GetEnemyUIComponent() const
{
    return nullptr;
}
