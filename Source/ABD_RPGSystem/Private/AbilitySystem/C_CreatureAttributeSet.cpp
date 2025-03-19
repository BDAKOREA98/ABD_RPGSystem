// ABD


#include "AbilitySystem/C_CreatureAttributeSet.h"


#include "GameplayEffectExtension.h"
#include "C_FunctionLibrary.h"
#include "C_GameplayTags.h"
#include "Interface/C_PawnUIInterface.h"
#include "Component/UI/C_PawnUIComponent.h"
#include "Component/UI/C_PlayerUIComponent.h"

#include "MyDebugHelper.h"
UC_CreatureAttributeSet::UC_CreatureAttributeSet()
{
	InitCurrentHealth(1.0f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefencePower(1.f);
}

void UC_CreatureAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IC_PawnUIInterface>(Data.Target.GetAvatarActor());

	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UC_PawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("Couldn't extarc a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());


	}
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.0f, GetMaxRage());

		SetCurrentRage(NewCurrentRage);

		if (GetCurrentRage() == GetMaxRage())
		{
			UC_FunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), BD_GamePlayTags::Player_Status_Rage_Full);

		}
		else if (GetCurrentRage() == 0.f)
		{
			UC_FunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), BD_GamePlayTags::Player_Status_Rage_None);

		}
		else
		{
			UC_FunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), BD_GamePlayTags::Player_Status_Rage_Full);
			UC_FunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), BD_GamePlayTags::Player_Status_Rage_None);
		}


		if (UC_PlayerUIComponent* PlayerUIComponent = CachedPawnUIInterface->GetPlayerUIComponent())
		{
			PlayerUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());

		}

	}
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);


		/*const FString DebugString = FString::Printf(TEXT("Old Health %f, Damage Done %f, NewCurrentHealth %f"),
			OldHealth,
			DamageDone,
			NewCurrentHealth

		);

		Debug::Print(DebugString, FColor::Green);*/

		//TODO :: Notify the UI
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());




		if (NewCurrentHealth == 0.0f)
		{
			UC_FunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), BD_GamePlayTags::Shared_Status_Dead);


		}
	}
}
