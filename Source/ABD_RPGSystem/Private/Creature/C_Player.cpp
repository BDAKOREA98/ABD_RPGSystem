// ABD


#include "Creature/C_Player.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/C_DA_InputConfig.h"
#include "Component/Input/C_InputComponent.h"
#include "C_GameplayTags.h"
#include "AbilitySystem/C_CreatureAbilitySystemComponent.h"
#include "DataAssets/StartUpData/C_DA_PlayerStartUpData.h"
#include "Component/Combat/C_PlayerCombatComponent.h"
#include "Component/UI/C_PlayerUIComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameModes/C_RPGGameMode.h"
#include "MyDebugHelper.h"
AC_Player::AC_Player()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 55.0f, 65.0f);
	CameraBoom->bUsePawnControlRotation = true;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;






	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;


	PlayerCombatComponent = CreateDefaultSubobject<UC_PlayerCombatComponent>(TEXT("PlayerCombatComponent"));
	PlayerUIComponent = CreateDefaultSubobject<UC_PlayerUIComponent>(TEXT("PlayerUIComponent"));
}

UC_PawnCombatComponent* AC_Player::GetPawnCombatComponent() const
{
	return PlayerCombatComponent;
}

UC_PawnUIComponent* AC_Player::GetPawnUIComponent() const
{
	return PlayerUIComponent;
}

UC_PlayerUIComponent* AC_Player::GetHeroUIComponent() const
{
    return PlayerUIComponent;
}

void AC_Player::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!CharacterStartUpData.IsNull())
	{
		if (UC_DA_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = 1;
			if (AC_RPGGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<AC_RPGGameMode>())
			{
				switch (BaseGameMode->GetCurrentGameDifficulty())
				{
				case EGameDifficulty::Easy:
					AbilityApplyLevel = 4;

					break;
				case EGameDifficulty::Normal:
					AbilityApplyLevel = 3;

					break;
				case EGameDifficulty::Hard:
					AbilityApplyLevel = 2;

					break;
				case EGameDifficulty::Hell:
					AbilityApplyLevel = 1;

					break;

				default:
					break;
				}
			}

			LoadedData->GiveToAbilitySystemComponent(CreatureAbilityComponent, AbilityApplyLevel);
		}
	}
}

void AC_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to Assign a valid data asset as input config"));


	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(SubSystem);

	SubSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UC_InputComponent* BD_InputComponent = CastChecked<UC_InputComponent>(PlayerInputComponent);

	BD_InputComponent->BindNativeInputAction(InputConfigDataAsset, BD_GamePlayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	BD_InputComponent->BindNativeInputAction(InputConfigDataAsset, BD_GamePlayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

	BD_InputComponent->BindNativeInputAction(InputConfigDataAsset, BD_GamePlayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggerd);
	BD_InputComponent->BindNativeInputAction(InputConfigDataAsset, BD_GamePlayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	BD_InputComponent->BindNativeInputAction(InputConfigDataAsset, BD_GamePlayTags::InputTag_PickUp_Stones, ETriggerEvent::Started, this, &ThisClass::Input_PickUpStonesStarted);

	BD_InputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleassed);

}

void AC_Player::BeginPlay()
{
	Super::BeginPlay();
}

void AC_Player::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

	if (MovementVector.Y != 0.0f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);

	}
	if (MovementVector.X != 0.0f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}

	

}

void AC_Player::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X != 0.0f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.0f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AC_Player::Input_SwitchTargetTriggerd(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void AC_Player::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f ? BD_GamePlayTags::Player_Event_SwitchTarget_Right : BD_GamePlayTags::Player_Event_SwitchTarget_Left,
		Data

	);
}

void AC_Player::Input_PickUpStonesStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		BD_GamePlayTags::Player_Event_ConsumeStones,
		Data
	);
}

void AC_Player::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	CreatureAbilityComponent->OnAbilityInputPressed(InInputTag);
}

void AC_Player::Input_AbilityInputReleassed(FGameplayTag InInputTag)
{
	CreatureAbilityComponent->OnAbilityInputReleassed(InInputTag);
}
