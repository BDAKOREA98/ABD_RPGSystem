// ABD


#include "Animation/Player/C_PlayerLinkedLayer.h"
#include "Animation/Player/C_PlayerAnimInstance.h"

UC_PlayerAnimInstance* UC_PlayerLinkedLayer::GetPlayerAnimInstance() const
{
    return  Cast<UC_PlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
