// ABD


#include "C_FunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"
#include "Interface/C_PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "C_GameplayTags.h"
#include "Types/CountDownAction.h"
#include "C_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/C_SaveGame.h"

#include "MyDebugHelper.h"

UC_CreatureAbilitySystemComponent* UC_FunctionLibrary::NativeGetCreatureASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UC_CreatureAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UC_FunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
    UC_CreatureAbilitySystemComponent* ASC = NativeGetCreatureASCFromActor(InActor);
  
    if (!ASC->HasMatchingGameplayTag(TagToAdd))
    {
        ASC->AddLooseGameplayTag(TagToAdd);
    }

}

void UC_FunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
       UC_CreatureAbilitySystemComponent* ASC = NativeGetCreatureASCFromActor(InActor);
    
       if (ASC->HasMatchingGameplayTag(TagToRemove))
       {
           ASC->RemoveLooseGameplayTag(TagToRemove);
       }
}

bool UC_FunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UC_CreatureAbilitySystemComponent* ASC = NativeGetCreatureASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UC_FunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ECreatureConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? ECreatureConfirmType::YES : ECreatureConfirmType::NO;

}

UC_PawnCombatComponent* UC_FunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
	if (IC_PawnCombatInterface* PawnCombatInterface = Cast<IC_PawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UC_PawnCombatComponent* UC_FunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, ECreatureValidType& OutValidType)
{
	UC_PawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	OutValidType = CombatComponent ? ECreatureValidType::Valid : ECreatureValidType::InValid;

	return CombatComponent;
}

bool UC_FunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}


	return false;

}

float UC_FunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UC_FunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDiffenece)
{
    check(InAttacker && InVictim);
    const FVector VictimForwad = InVictim->GetActorForwardVector();
    const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

    const float DotResult = FVector::DotProduct(VictimForwad, VictimToAttackerNormalized);
    OutAngleDiffenece = UKismetMathLibrary::DegAcos(DotResult);


    const FVector CrossResult = FVector::CrossProduct(VictimForwad, VictimToAttackerNormalized);

    if (CrossResult.Z < 0.0f)
    {
        OutAngleDiffenece *= -1.f;

    }

    if (OutAngleDiffenece >= -45.f && OutAngleDiffenece <= 45.f)
    {
        return BD_GamePlayTags::Shared_Status_HitReact_Front;
    }
    else if (OutAngleDiffenece < -45.f && OutAngleDiffenece >= -135.f)
    {
        return BD_GamePlayTags::Shared_Status_HitReact_Left;

    }
    else if (OutAngleDiffenece < -135.f || OutAngleDiffenece > 135.f)
    {
        return BD_GamePlayTags::Shared_Status_HitReact_Back;

    }
    else if (OutAngleDiffenece > 45.f && OutAngleDiffenece <= 135.f)
    {
        return BD_GamePlayTags::Shared_Status_HitReact_Right;

    }



    return BD_GamePlayTags::Shared_Status_HitReact_Front;
}

bool UC_FunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
    check(InAttacker && InDefender);

    const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());



    //const FString DebugString = FString::Printf(TEXT("Dot Result : %f %f"), DotResult, DotResult < -0.1f ? TEXT("Valid Block") : TEXT("InvalidBlock"));
    //
    // Print(DebugString, DotResult < -0.1f ? FColor::Green : FColor::Red);



    return DotResult < -0.1f;
}

bool UC_FunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
    UC_CreatureAbilitySystemComponent* SourceASC = NativeGetCreatureASCFromActor(InInstigator);
    UC_CreatureAbilitySystemComponent* TargetASC = NativeGetCreatureASCFromActor(InTargetActor);

    FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);



    return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}


void UC_FunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, ECreatureCountDownActionInput CountDownInput, UPARAM(DisplayName = "Output") ECreatureCountDownActionOutput& CountDownOutPut, FLatentActionInfo LatentInfo)
{
    UWorld* World = nullptr;

    if (GEngine)
    {
        World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    }

    if (!World)
    {
        return;
    }


    FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

    FCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);

    if (CountDownInput == ECreatureCountDownActionInput::Start)
    {
        if (!FoundAction)
        {
            LatentActionManager.AddNewAction(
                LatentInfo.CallbackTarget,
                LatentInfo.UUID,
                new FCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutPut, LatentInfo)

            );


        }
    }

    if (CountDownInput == ECreatureCountDownActionInput::Cancel)
    {
        if (FoundAction)
        {
            FoundAction->CancelAction();

        }
    }

}

UC_GameInstance* UC_FunctionLibrary::GetGameInstance(const UObject* WorldContextObject)
{
    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            return World->GetGameInstance<UC_GameInstance>();
        }
    }
    return nullptr;
}

void UC_FunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EInputMode InInputMode)
{
    APlayerController* PlayerController = nullptr;

    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            PlayerController = World->GetFirstPlayerController();
        }
    }

    if (!PlayerController)
    {
        return;
    }

    FInputModeGameOnly GameOnlyMode;
    FInputModeUIOnly UIOnlyMode;
    switch (InInputMode)
    {
    case EInputMode::GameOnly:
        PlayerController->SetInputMode(GameOnlyMode);
        PlayerController->bShowMouseCursor = false;

        break;
    case EInputMode::UIOnly:
        PlayerController->SetInputMode(UIOnlyMode);
        PlayerController->bShowMouseCursor = true;
        break;
    default:
        break;
    }
}

void UC_FunctionLibrary::SaveCurrentGameDifficulty(EGameDifficulty InDifficultyToSave)
{
    USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(UC_SaveGame::StaticClass());
    if (UC_SaveGame* MySaveGameObject = Cast<UC_SaveGame>(SaveGameObject))
    {
        MySaveGameObject->SavedCurrentGameDifficulty = InDifficultyToSave;

        const bool bWasSaved = UGameplayStatics::SaveGameToSlot(MySaveGameObject, BD_GamePlayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);
        // Debug::Print(bWasSaved ? TEXT("Difficulty Saved") : TEXT("Difficulty No Saved"));

    }
}

bool UC_FunctionLibrary::TryLoadSavedGameDifficulty(EGameDifficulty& OutDifficultyToSave)
{
    if (UGameplayStatics::DoesSaveGameExist(BD_GamePlayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0))
    {
        USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(BD_GamePlayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);

        if (UC_SaveGame* MySaveGameObject = Cast<UC_SaveGame>(SaveGameObject))
        {
            OutDifficultyToSave = MySaveGameObject->SavedCurrentGameDifficulty;

            //Debug::Print(TEXT("Loading Successful"), FColor::Green);

            return true;
        }

    }

    return false;
}
