// Fill out your copyright notice in the Description page of Project Settings.


#include "TestRepComponent.h"
#include "tps.pb.h"
#include "unreal_common.pb.h"
#include "GameFramework/Character.h"

const google::protobuf::Message* UTestRepComponent::GetStateFromChannelData(google::protobuf::Message* ChannelData, UObject* TargetObject, uint32 NetGUID, bool& bIsRemoved)
{
	auto TestRepChannelData = static_cast<tpspb::TestRepChannelData*>(ChannelData);
	if (TargetObject->IsA<USceneComponent>())
	{
		auto States = TestRepChannelData->mutable_scenecomponentstates();
		if (States->contains(NetGUID))
		{
			auto State = &States->at(NetGUID);
			bIsRemoved = State->removed();
			return State;
		}
	}
	else if (TargetObject->IsA<ACharacter>())
	{
		auto States = TestRepChannelData->mutable_characterstates();
		if (States->contains(NetGUID))
		{
			auto State = &States->at(NetGUID);
			bIsRemoved = State->removed();
			return State;
		}
	}
	
	bIsRemoved = false;
	return nullptr;
}

void UTestRepComponent::SetStateToChannelData(const google::protobuf::Message* State, google::protobuf::Message* ChannelData, UObject* TargetObject, uint32 NetGUID)
{
	auto TestRepChannelData = static_cast<tpspb::TestRepChannelData*>(ChannelData);
	if (TargetObject->IsA<USceneComponent>())
	{
		auto SceneCompState = static_cast<const unrealpb::SceneComponentState*>(State);
		auto States = TestRepChannelData->mutable_scenecomponentstates();
		(*States)[NetGUID] = *SceneCompState;
	}
	else if (TargetObject->IsA<ACharacter>())
	{
		auto CharacterState = static_cast<const unrealpb::CharacterState*>(State);
		auto States = TestRepChannelData->mutable_characterstates();
		(*States)[NetGUID] = *CharacterState;
	}
}

google::protobuf::Message* UTestRepComponent::GetChannelDataTemplate() const
{
	return new tpspb::TestRepChannelData;
}