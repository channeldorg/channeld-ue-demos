// Fill out your copyright notice in the Description page of Project Settings.


#include "TestRepChanneldActor.h"
#include "tps.pb.h"

const unrealpb::SceneComponentState* ATestRepChanneldActor::GetSceneComponentStateFromChannelData(const google::protobuf::Message* ChannelData)
{
	uint32 NetGUID = GetNetGUID();
	if (NetGUID > 0)
	{
		auto TestRepChannelData = static_cast<const tpspb::TestRepChannelData*>(ChannelData);
		const unrealpb::SceneComponentState& Result = TestRepChannelData->scenecomponentstates().at(NetGUID);
		return &Result;
	}
	else
	{
		return nullptr;//unrealpb::SceneComponentState::default_instance();
	}
}

void ATestRepChanneldActor::SetSceneComponentStateToChannelData(unrealpb::SceneComponentState* State, google::protobuf::Message* ChannelData)
{
	uint32 NetGUID = GetNetGUID();
	if (NetGUID > 0)
	{
		auto TestRepChannelData = static_cast<tpspb::TestRepChannelData*>(ChannelData);
		auto States = TestRepChannelData->mutable_scenecomponentstates();
		(*States)[NetGUID] = *State;
	}
}

google::protobuf::Message* ATestRepChanneldActor::GetChannelDataTemplate() const
{
	return new tpspb::TestRepChannelData;
}
