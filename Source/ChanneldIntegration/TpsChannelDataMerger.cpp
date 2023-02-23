#include "TpsChannelDataMerger.h"

#include "tps.pb.h"

bool FTpsChannelDataMerger::Merge(const google::protobuf::Message* SrcMsg, google::protobuf::Message* DstMsg)
{
	auto Src = static_cast<const tpspb::TestRepChannelData*>(SrcMsg);
	auto Dst = static_cast<tpspb::TestRepChannelData*>(DstMsg);
	
	if (Src->has_gamestate())
	{
		Dst->mutable_gamestate()->MergeFrom(Src->gamestate());
	}
	if (Src->has_testgamestate())
	{
		Dst->mutable_testgamestate()->MergeFrom(Dst->testgamestate());
	}

	for (auto& Pair : Src->actorstates())
	{
		if (Pair.second.removed())
		{
			Dst->mutable_actorstates()->erase(Pair.first);
			Dst->mutable_pawnstates()->erase(Pair.first);
			Dst->mutable_characterstates()->erase(Pair.first);
			Dst->mutable_controllerstates()->erase(Pair.first);
			Dst->mutable_playercontrollerstates()->erase(Pair.first);
			Dst->mutable_testrepplayercontrollerstates()->erase(Pair.first);
		}
		else
		{
			if (Dst->actorstates().contains(Pair.first))
			{
				Dst->mutable_actorstates()->at(Pair.first).MergeFrom(Pair.second);
			}
			else
			{
				Dst->mutable_actorstates()->emplace(Pair.first, Pair.second);
			}
		}
	}

	for (auto& Pair : Src->pawnstates())
	{
		if (Dst->pawnstates().contains(Pair.first))
		{
			Dst->mutable_pawnstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_pawnstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->characterstates())
	{
		if (Dst->characterstates().contains(Pair.first))
		{
			Dst->mutable_characterstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_characterstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->playerstates())
	{
		if (Dst->playerstates().contains(Pair.first))
		{
			Dst->mutable_playerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_playerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->controllerstates())
	{
		if (Dst->controllerstates().contains(Pair.first))
		{
			Dst->mutable_controllerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_controllerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->playercontrollerstates())
	{
		if (Dst->playercontrollerstates().contains(Pair.first))
		{
			Dst->mutable_playercontrollerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_playercontrollerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->testrepplayercontrollerstates())
	{
		if (Dst->testrepplayercontrollerstates().contains(Pair.first))
		{
			Dst->mutable_testrepplayercontrollerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_testrepplayercontrollerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->actorcomponentstates())
	{
		if (Dst->actorcomponentstates().contains(Pair.first))
		{
			Dst->mutable_actorcomponentstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_actorcomponentstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->scenecomponentstates())
	{
		if (Dst->scenecomponentstates().contains(Pair.first))
		{
			Dst->mutable_scenecomponentstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_scenecomponentstates()->emplace(Pair.first, Pair.second);
		}
	}

	return true;
}
