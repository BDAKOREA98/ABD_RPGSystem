// ABD


#include "Types/CountDownAction.h"


void FCountDownAction::UpdateOperation(FLatentResponse& Response)
{
	if (bNeedToCancel)
	{
		CountDownOutput = ECreatureCountDownActionOutput::Cancelled;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);

		return;
	}

	if (ElapsedTimeSinceStart >= TotalCountDownTime)
	{
		CountDownOutput = ECreatureCountDownActionOutput::Completed;
		Response.FinishAndTriggerIf(true, ExecutionFunction, OutputLink, CallbackTarget);
		return;
	}

	if (ElapsedInterval < UpdateInterval)
	{
		ElapsedInterval += Response.ElapsedTime();

	}
	else
	{
		ElapsedTimeSinceStart += UpdateInterval > 0.f ? UpdateInterval : Response.ElapsedTime();

		OutRemainingTime = TotalCountDownTime - ElapsedTimeSinceStart;

		CountDownOutput = ECreatureCountDownActionOutput::Updated;

		Response.TriggerLink(ExecutionFunction, OutputLink, CallbackTarget);

		ElapsedInterval = 0.f;

	}
}

void FCountDownAction::CancelAction()
{
	bNeedToCancel = true;
}
