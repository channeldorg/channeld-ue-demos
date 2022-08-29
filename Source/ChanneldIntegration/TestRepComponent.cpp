// Fill out your copyright notice in the Description page of Project Settings.


#include "TestRepComponent.h"
#include "tps.pb.h"

const unrealpb::SceneComponentState* UTestRepComponent::GetSceneComponentStateFromChannelData(google::protobuf::Message* ChannelData, uint32 NetGUID)
{
	auto TestRepChannelData = static_cast<tpspb::TestRepChannelData*>(ChannelData);
	auto States = TestRepChannelData->mutable_scenecomponentstates();
	if (States->contains(NetGUID))
	{
		return &States->at(NetGUID);
	}

	return nullptr;//unrealpb::SceneComponentState::default_instance();
}

void UTestRepComponent::SetSceneComponentStateToChannelData(unrealpb::SceneComponentState* State, google::protobuf::Message* ChannelData, uint32 NetGUID)
{
	auto TestRepChannelData = static_cast<tpspb::TestRepChannelData*>(ChannelData);
	auto States = TestRepChannelData->mutable_scenecomponentstates();
	(*States)[NetGUID] = *State;
}

google::protobuf::Message* UTestRepComponent::GetChannelDataTemplate() const
{
	return new tpspb::TestRepChannelData;
}