// ABD


#include "Controller/C_AIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"


#include "MyDebugHelper.h"
AC_AIController::AC_AIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	EnemyAISenseConfig_Sight = CreateDefaultSubobject< UAISenseConfig_Sight>("EnemyAISenseConfig_Sight");
	EnemyAISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	EnemyAISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	EnemyAISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	EnemyAISenseConfig_Sight->SightRadius = 5000.f;
	EnemyAISenseConfig_Sight->LoseSightRadius = 0.f;
	EnemyAISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;


	EnemyPerceptionComponent = CreateDefaultSubobject< UAIPerceptionComponent>("EnemyPerceptionComponent");
	EnemyPerceptionComponent->ConfigureSense(*EnemyAISenseConfig_Sight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPercepationUpdated);


	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AC_AIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);


	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());

	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}

	return ETeamAttitude::Friendly;


}

void AC_AIController::BeginPlay()
{
	Super::BeginPlay();


	if (UCrowdFollowingComponent* CrowdComp = Cast< UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdComp->SetCrowdSimulationState(bEnableDetourCrowdAboidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidanceQuality)
		{
		case 1: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);

			break;
		case 2: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);

			break;
		case 3: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);

			break;
		case 4: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);

			break;

		default:
			break;
		}

		CrowdComp->SetAvoidanceGroup(1);
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange(CollisionQueryRange);

	}
}

void AC_AIController::OnEnemyPercepationUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			if (Stimulus.WasSuccessfullySensed() && Actor)
			{
				BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
			}
		}
	}
}
