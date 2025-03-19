// ABD


#include "Creature/C_Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/Combat/C_EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/C_DA_StartUpDataBase.h"
#include "DataAssets/StartUpData/C_DA_EnemyStartUpData.h"
#include "Components/WidgetComponent.h"
#include "Component/UI/C_EnemyUIComponent.h"
#include "Widget/C_WidgetBase.h"
#include "Components/BoxComponent.h"
#include "C_FunctionLibrary.h"
#include "GameModes/C_RPGGameMode.h"
#include "MyDebugHelper.h"

AC_Enemy::AC_Enemy()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;


	EnemyCombatComponent = CreateDefaultSubobject< UC_EnemyCombatComponent>("EnemyCombatComponent");

	EnemyUIComponent = CreateDefaultSubobject< UC_EnemyUIComponent>("EnemyUIComponent");

	EnemyHealthWidgetComponent = CreateDefaultSubobject< UWidgetComponent>("EnemyHealthWidgetComponent");
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());


	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollision");
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);

	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollision");
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
}

UC_PawnCombatComponent* AC_Enemy::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UC_PawnUIComponent* AC_Enemy::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UC_EnemyUIComponent* AC_Enemy::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}
void AC_Enemy::BeginPlay()
{
	Super::BeginPlay();

	if (UC_WidgetBase* HealthWidget = Cast<UC_WidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreateWidget(this);
	}


}

void AC_Enemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void AC_Enemy::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
}

void AC_Enemy::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UC_FunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			EnemyCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
}

void AC_Enemy::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}
	
	int32 AbilityApplyLevel = 1;
	if (AC_RPGGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<AC_RPGGameMode>())
	{
		switch (BaseGameMode->GetCurrentGameDifficulty())
		{
		case EGameDifficulty::Easy:
			AbilityApplyLevel = 1;
			break;
		case EGameDifficulty::Normal:
			AbilityApplyLevel = 2;
			break;
		case EGameDifficulty::Hard:
			AbilityApplyLevel = 3;
			break;
		case EGameDifficulty::Hell:
			AbilityApplyLevel = 4;
			break;
	
		default:
			break;
		}
	}
	
	
	UAssetManager::GetStreamableManager().RequestAsyncLoad
	(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda
		(
			[this, AbilityApplyLevel]()
			{
				if (UC_DA_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
	
	
					LoadedData->GiveToAbilitySystemComponent(CreatureAbilityComponent, AbilityApplyLevel);
	
	
	
	
				}
	
			}
		)
	
	);
}
