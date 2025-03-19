// ABD


#include "Creature/C_Player.h"

AC_Player::AC_Player()
{
}

UC_PawnCombatComponent* AC_Player::GetPawnCombatComponent() const
{
    return nullptr;
}

UC_PawnUIComponent* AC_Player::GetPawnUIComponent() const
{
    return nullptr;
}

UC_PlayerUIComponent* AC_Player::GetHeroUIComponent() const
{
    return nullptr;
}

void AC_Player::PossessedBy(AController* NewController)
{
}

void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

void AC_Player::BeginPlay()
{
}

void AC_Player::Input_Move(const FInputActionValue& InputActionValue)
{
}

void AC_Player::Input_Look(const FInputActionValue& InputActionValue)
{
}

void AC_Player::Input_SwitchTargetTriggerd(const FInputActionValue& InputActionValue)
{
}

void AC_Player::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
}

void AC_Player::Input_PickUpStonesStarted(const FInputActionValue& InputActionValue)
{
}

void AC_Player::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
}

void AC_Player::Input_AbilityInputReleassed(FGameplayTag InInputTag)
{
}
