#pragma once
#include "ChannelDataInterfaces.h"

class CHANNELDINTEGRATION_API FTpsEntityChannelDataProcessor : public IChannelDataProcessor
{
public:
	virtual bool Merge(const google::protobuf::Message* SrcMsg, google::protobuf::Message* DstMsg) override;

	virtual const google::protobuf::Message* GetStateFromChannelData(google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bIsRemoved) override;
	virtual void SetStateToChannelData(const google::protobuf::Message* State, google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID) override;

	virtual TArray<uint32> GetRelevantNetGUIDsFromChannelData(const google::protobuf::Message* ChannelData) override;
};