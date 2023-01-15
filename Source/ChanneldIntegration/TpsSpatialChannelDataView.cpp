// Fill out your copyright notice in the Description page of Project Settings.


#include "TpsSpatialChannelDataView.h"

#include "tps.pb.h"

TArray<uint32> UTpsSpatialChannelDataView::GetNetGUIDsFromChannelData(const google::protobuf::Message* Message)
{
	auto ChannelData = static_cast<const tpspb::TestRepChannelData*>(Message);
	TArray<uint32> NetGUIDs;
	for (auto& Pair : ChannelData->actorstates())
	{
		// Ignore GameState
		if (Pair.first == GameStateNetId)
		{
			continue;
		}
		// Ignore Controllers
		if (ChannelData->controllerstates_size() > 0 && ChannelData->controllerstates().contains(Pair.first))
		{
			continue;
		}
		// Ignore PlayerStates
		if (ChannelData->playerstates_size() > 0 && ChannelData->playerstates().contains(Pair.first))
		{
			continue;
		}
		NetGUIDs.Add(Pair.first);
	}
	return NetGUIDs;
}
