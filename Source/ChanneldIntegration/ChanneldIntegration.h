#pragma once

#include "CoreMinimal.h"
#include "TpsChannelDataProcessor.h"
#include "TpsEntityChannelDataProcessor.h"
#include "TpsSpatialChannelDataProcessor.h"
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
	FTpsSpatialChannelDataProcessor* SpatialChannelDataProcessor;
	FTpsEntityChannelDataProcessor* EntityChannelDataProcessor;
};

