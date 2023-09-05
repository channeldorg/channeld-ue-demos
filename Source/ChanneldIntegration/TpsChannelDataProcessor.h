#pragma once
#include "ChannelDataInterfaces.h"

class CHANNELDINTEGRATION_API FTpsChannelDataProcessor : public IChannelDataProcessor
{
public:
	FTpsChannelDataProcessor();
	virtual bool Merge(const google::protobuf::Message* SrcMsg, google::protobuf::Message* DstMsg) override;

	virtual const google::protobuf::Message* GetStateFromChannelData(google::protobuf::Message* ChannelData, UClass* TargetClass, UObject* TargetObject, uint32 NetGUID, bool& bIsRemoved) override;
	virtual void SetStateToChannelData(const google::protobuf::Message* State, google::protobuf::Message* ChannelData, UClass* TargetClass, UObject* TargetObject, uint32 NetGUID) override;

protected:
	TUniquePtr<unrealpb::ActorState> RemovedActorState;
	TUniquePtr<unrealpb::ActorComponentState> RemovedActorComponentState;
	TUniquePtr<unrealpb::SceneComponentState> RemovedSceneComponentState;
};