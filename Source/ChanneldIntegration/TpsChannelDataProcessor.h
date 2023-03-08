#pragma once
#include "ChannelDataInterfaces.h"

class FTpsChannelDataProcessor : public IChannelDataProcessor
{
public:
	FTpsChannelDataProcessor();
	virtual bool Merge(const google::protobuf::Message* SrcMsg, google::protobuf::Message* DstMsg) override;

	virtual const google::protobuf::Message* GetStateFromChannelData(google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bIsRemoved) override;
	virtual void SetStateToChannelData(const google::protobuf::Message* State, google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID) override;

	virtual TArray<uint32> GetRelevantNetGUIDsFromChannelData(const google::protobuf::Message* ChannelData) override;

protected:
	TUniquePtr<unrealpb::ActorState> RemovedActorState;
	TUniquePtr<unrealpb::ActorComponentState> RemovedActorComponentState;
};