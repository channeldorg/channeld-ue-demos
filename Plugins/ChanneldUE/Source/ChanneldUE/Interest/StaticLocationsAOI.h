#pragma once

#include "AreaOfInterestBase.h"

class CHANNELDUE_API FStaticLocationsAOI : public UAreaOfInterestBase
{
public:
	TArray<FVector> Spots;

protected:
	virtual void SetSpatialQuery(channeldpb::SpatialInterestQuery* Query, const FVector& PawnLocation, const FRotator& PawnRotation) override;
};