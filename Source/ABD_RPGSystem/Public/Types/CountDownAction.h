// ABD

#pragma once

#include "CoreMinimal.h"
#include "EnumTypes.h"
#include "Engine/World.h"
/**
 * 
 */
class FCountDownAction : public FPendingLatentAction
{
public:

	FCountDownAction(float InTotalCountDownTime, float InUpdateInterval, float& InOutRemainingTime, ECreatureCountDownActionOutput& InCountDownOutput, const FLatentActionInfo& LatentInfo)
		: bNeedToCancel(false)
		, TotalCountDownTime(InTotalCountDownTime)
		, UpdateInterval(InUpdateInterval)
		, OutRemainingTime(InOutRemainingTime)
		, CountDownOutput(InCountDownOutput)
		, ExecutionFunction(LatentInfo.ExecutionFunction)
		, OutputLink(LatentInfo.Linkage)
		, CallbackTarget(LatentInfo.CallbackTarget)
		, ElapsedInterval(0.f)
		, ElapsedTimeSinceStart(0.f) {
	}


	virtual void UpdateOperation(FLatentResponse& Response) override;



	void CancelAction();

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	ECreatureCountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};