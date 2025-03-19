// ABD


#include "AbilitySystem/Abilities/C_Player_LockOn_GameplayAbility.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Creature/C_Player.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/C_WidgetBase.h"
#include "Controller/C_PlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "C_FunctionLibrary.h"
#include "C_GameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"

#include "MyDebugHelper.h"
void UC_Player_LockOn_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();


	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UC_Player_LockOn_GameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();
	CleanUp();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UC_Player_LockOn_GameplayAbility::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor ||
		UC_FunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor, BD_GamePlayTags::Shared_Status_Dead) ||
		UC_FunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), BD_GamePlayTags::Shared_Status_Dead))
	{
		CancelTargetLockAbility();

		return;
	}

	SetTargetLockWidgetPosition();

	const bool bShouldOverrideRotation =
		!UC_FunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), BD_GamePlayTags::Player_Status_Rolling)
		&&
		!UC_FunctionLibrary::NativeDoesActorHaveTag(GetPlayerCharacterFromActorInfo(), BD_GamePlayTags::Player_Status_Blocking);


	if (bShouldOverrideRotation)
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
			GetPlayerCharacterFromActorInfo()->GetActorLocation(),
			CurrentLockedActor->GetActorLocation()
		);

		LookAtRot -= FRotator(TargetLockCameraOffsetDistance_X, TargetLockCameraOffsetDistance_Y, 0.0f);


		const FRotator CurrentControlRot = GetPlayerControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);

		GetPlayerControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.0f));
		GetPlayerCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	}

}

void UC_Player_LockOn_GameplayAbility::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	GetAvailableActorsToLock();
	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	AActor* NewTargetToLock = nullptr;

	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);

	if (InSwitchDirectionTag == BD_GamePlayTags::Player_Event_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}

	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}
}

void UC_Player_LockOn_GameplayAbility::TryLockOnTarget()
{
	GetAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	InitTargetLockMovement();
	InitTargetLockMappingContext();

	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else
	{
		CancelTargetLockAbility();
	}
}

void UC_Player_LockOn_GameplayAbility::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();

	TArray<FHitResult> BoxTraceHits;


	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetPlayerCharacterFromActorInfo(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetPlayerCharacterFromActorInfo()->GetActorLocation() + GetPlayerCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.0f,
		GetPlayerCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistenDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetPlayerCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);


			}


		}

	}
}

AActor* UC_Player_LockOn_GameplayAbility::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.0f;

	return UGameplayStatics::FindNearestActor(GetPlayerCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);
}

void UC_Player_LockOn_GameplayAbility::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight)
{
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	const FVector PlayerLocation = GetPlayerCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
	for (AActor* AvailableActor : AvailableActorsToLock)
	{

		if (!AvailableActor || AvailableActor == CurrentLockedActor)
		{
			continue;
		}
		const FVector PlayerToAvailableNormaized = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

		const FVector CrossResult = FVector::CrossProduct(PlayerToCurrentNormalized, PlayerToAvailableNormaized);
		if (CrossResult.Z > 0.f)
		{
			OutActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			OutActorsOnLeft.AddUnique(AvailableActor);
		}

	}
}

void UC_Player_LockOn_GameplayAbility::DrawTargetLockWidget()
{
	if (!TargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Forgot to assign a valid widget class in blueprint"));

		TargetLockWidget = CreateWidget< UC_WidgetBase>(GetPlayerControllerFromActorInfo(), TargetLockWidgetClass);

		check(TargetLockWidget);

		TargetLockWidget->AddToViewport();
	}




}

void UC_Player_LockOn_GameplayAbility::SetTargetLockWidgetPosition()
{
	if (!TargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;

	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetPlayerControllerFromActorInfo(),
		CurrentLockedActor->GetActorLocation(),
		ScreenPosition,
		true

	);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		TargetLockWidget->WidgetTree->ForEachWidget(
			[this](UWidget* FoundWidget)
			{
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
				{
					TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();


				}
			}
		);
	}



	ScreenPosition -= (TargetLockWidgetSize / 2.0f);


	TargetLockWidget->SetPositionInViewport(ScreenPosition, false);
}

void UC_Player_LockOn_GameplayAbility::InitTargetLockMovement()
{
	CachedDefaultMaxWalkSpeed = GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;

	GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;
}

void UC_Player_LockOn_GameplayAbility::InitTargetLockMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(SubSystem);

	SubSystem->AddMappingContext(TargetLockMappingContext, 3);
}

void UC_Player_LockOn_GameplayAbility::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);

}

void UC_Player_LockOn_GameplayAbility::CleanUp()
{
	AvailableActorsToLock.Empty();

	CurrentLockedActor = nullptr;

	if (TargetLockWidget)
	{
		TargetLockWidget->RemoveFromParent();
	}

	TargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
}

void UC_Player_LockOn_GameplayAbility::ResetTargetLockMovement()
{
	if (CachedDefaultMaxWalkSpeed > 0.f)
	{
		GetPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
	}
}

void UC_Player_LockOn_GameplayAbility::ResetTargetLockMappingContext()
{
	if (!GetPlayerControllerFromActorInfo())
	{
		return;
	}

	const ULocalPlayer* LocalPlayer = GetPlayerControllerFromActorInfo()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(SubSystem);

	SubSystem->RemoveMappingContext(TargetLockMappingContext);
}
