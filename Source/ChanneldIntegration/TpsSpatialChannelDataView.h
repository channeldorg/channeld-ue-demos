#pragma once

#include "CoreMinimal.h"
#include "View/SpatialChannelDataView.h"
#include "TpsSpatialChannelDataView.generated.h"

UCLASS()
class CHANNELDINTEGRATION_API UTpsSpatialChannelDataView : public USpatialChannelDataView
{
	GENERATED_BODY()

protected:
	virtual TArray<uint32> GetRelevantNetGUIDsFromChannelData(const google::protobuf::Message* Message) override;
};