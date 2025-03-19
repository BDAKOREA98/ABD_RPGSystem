#pragma once
UENUM()
enum class ECreatureConfirmType : uint8
{
	YES,
	NO
};

UENUM()
enum class ECreatureValidType : uint8
{
	Valid,
	InValid
};
UENUM()
enum class ECreatureSuccessType : uint8
{
	Succesful,
	Failed
};
UENUM()
enum class ECreatureCountDownActionInput : uint8
{
	Start,
	Cancel
};
UENUM()
enum class ECreatureCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled
};

UENUM(BlueprintType)
enum class EGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	Hell
};
UENUM(BlueprintType)
enum class EInputMode :uint8
{
	GameOnly,
	UIOnly
};



