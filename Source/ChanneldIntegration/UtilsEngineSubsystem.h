#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "UtilsEngineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class CHANNELDINTEGRATION_API UUtilsEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utils|Time")
		static void GetNowTimestamp(int64& Now);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utils|Time")
		static void TimestampToDateTime(FDateTime& DateTime, int64 Timestamp);

};
