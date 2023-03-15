#pragma once

#include "CoreMinimal.h"
#include "TpsChannelDataProcessor.h"
#include "Modules/ModuleManager.h"

class FChanneldIntegrationModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool IsGameModule() const override
	{
		return true;
	}

	FTpsChannelDataProcessor* TpsChannelDataProcessor;
};

