// ABD


#include "Controller/C_PlayerController.h"

AC_PlayerController::AC_PlayerController()
{
    PlayerTeamID = FGenericTeamId(0);
}

FGenericTeamId AC_PlayerController::GetGenericTeamId() const
{
    return PlayerTeamID;
}
