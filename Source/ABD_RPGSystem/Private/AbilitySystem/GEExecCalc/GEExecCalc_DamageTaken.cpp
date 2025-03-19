// ABD


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/C_CreatureAttributeSet.h"
#include "C_GameplayTags.h"

#include "MyDebugHelper.h"

struct FDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefencePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UC_CreatureAttributeSet, AttackPower, Source, false)
			DEFINE_ATTRIBUTE_CAPTUREDEF(UC_CreatureAttributeSet, DefencePower, Target, false)
			DEFINE_ATTRIBUTE_CAPTUREDEF(UC_CreatureAttributeSet, DamageTaken, Target, false)
	}

};

static const FDamageCapture& GetWarriorDamageCapture()
{
	static FDamageCapture DamageCapture;
	return DamageCapture;
}


UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefencePowerDef);
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DamageTakenDef);


}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	//EffectSpec.GetContext().GetSourceObject();
	//EffectSpec.GetContext().GetAbility();
	//EffectSpec.GetContext().GetInstigator();
	//EffectSpec.GetContext().GetEffectCauser();




	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();




	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
	//Debug::Print(TEXT("SourceAttackPower"), SourceAttackPower);


	float BaseDamage = 0.0f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;


	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(BD_GamePlayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}

		if (TagMagnitude.Key.MatchesTagExact(BD_GamePlayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedLightAttackComboCount"), UsedLightAttackComboCount);
		}
		if (TagMagnitude.Key.MatchesTagExact(BD_GamePlayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedHeavyAttackComboCount"), UsedHeavyAttackComboCount);
		}

	}


	float TargetDefencePower = 0.0f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DefencePowerDef, EvaluateParameters, TargetDefencePower);
	//Debug::Print(TEXT("TargetDefencePower"), TargetDefencePower);


	if (UsedLightAttackComboCount != 0)
	{
		const float DamageInCreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05f + 1.0f;

		BaseDamage *= DamageInCreasePercentLight;
		//Debug::Print(TEXT("ScaledBaseDamageLight"), BaseDamage);
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageInCreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.0f;

		BaseDamage *= DamageInCreasePercentHeavy;
		//Debug::Print(TEXT("ScaledBaseDamageHeavy"), BaseDamage);

	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefencePower;

	//Debug::Print(TEXT("FinalDamageDone"), FinalDamageDone);

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetWarriorDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone

			)
		);
	}
}
