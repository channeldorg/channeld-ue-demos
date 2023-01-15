// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateRepComponent.h"

#include "tps.pb.h"
#include "unreal_common.pb.h"
#include "GameFramework/GameStateBase.h"
#include "TestRepComponent.h"

UGameStateRepComponent::UGameStateRepComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const google::protobuf::Message* UGameStateRepComponent::GetStateFromChannelData(google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bIsRemoved)
{
	auto GlobalChannelData = static_cast<tpspb::GlobalChannelData*>(ChannelData);
	if (TargetClass == AGameStateBase::StaticClass())
	{
		bIsRemoved = false;
		return GlobalChannelData->mutable_gamestate();
	}
	else
	{
		UE_LOG(LogChanneldTest, Warning, TEXT("State of '%s' is not supported in the ChannelData, NetGUID: %d"), *TargetClass->GetName(), NetGUID);
	}
	
	bIsRemoved = false;
	return nullptr;
}

void UGameStateRepComponent::SetStateToChannelData(const google::protobuf::Message* State, google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID)
{
	auto GlobalChannelData = static_cast<tpspb::GlobalChannelData*>(ChannelData);
	if (TargetClass == AGameStateBase::StaticClass())
	{
		auto GameState = static_cast<const unrealpb::GameStateBase*>(State);
		if (GameState)
		{
			GlobalChannelData->mutable_gamestate()->MergeFrom(*GameState);
		}
	}
	else
	{
		UE_LOG(LogChanneldTest, Warning, TEXT("State of '%s' is not supported in the ChannelData, NetGUID: %d"), *TargetClass->GetName(), NetGUID);
	}
}
