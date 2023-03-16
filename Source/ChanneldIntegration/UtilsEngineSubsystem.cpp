#include "UtilsEngineSubsystem.h"

void UUtilsEngineSubsystem::GetNowTimestamp(int64& Now)
{
	FDateTime Time = FDateTime::Now();
	Now = Time.ToUnixTimestamp();
}

void UUtilsEngineSubsystem::TimestampToDateTime(FDateTime& DateTime, int64 Timestamp)
{
	DateTime = FDateTime::FromUnixTimestamp(Timestamp);
}
