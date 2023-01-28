// Fill out your copyright notice in the Description page of Project Settings.


#include "TpsSpatialChannelDataView.h"

#include "tps.pb.h"

TSet<uint32> UTpsSpatialChannelDataView::GetNetGUIDsFromChannelData(const google::protobuf::Message* Message)
{
	auto ChannelData = static_cast<const tpspb::TestRepChannelData*>(Message);
	TSet<uint32> NetGUIDs;
	for (auto& Pair : ChannelData->actorstates())
	{
		/* Instead of using a blacklist, we should use a whitelist as the data in the blacklist may not exist in the ChannelData.
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
		*/

		if (ChannelData->pawnstates_size() > 0 && ChannelData->pawnstates().contains(Pair.first))
		{
			NetGUIDs.Add(Pair.first);
		}
		else if (ChannelData->characterstates_size() > 0 && ChannelData->characterstates().contains(Pair.first))
		{
			NetGUIDs.Add(Pair.first);
		}
		else if (ChannelData->scenecomponentstates_size() > 0 && ChannelData->scenecomponentstates().contains(Pair.first))
		{
			NetGUIDs.Add(Pair.first);
		}
	}
	return NetGUIDs;
}
