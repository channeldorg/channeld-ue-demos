#include "TpsSpatialChannelDataProcessor.h"

#include "GameFramework/PlayerState.h"

bool FTpsSpatialChannelDataProcessor::Merge(const google::protobuf::Message* SrcMsg, google::protobuf::Message* DstMsg)
{
	DstMsg->MergeFrom(*SrcMsg);
	return true;
}

const google::protobuf::Message* FTpsSpatialChannelDataProcessor::GetStateFromChannelData(
	google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bIsRemoved)
{
	auto SpatialChannelData = static_cast<unrealpb::SpatialChannelData*>(ChannelData);
	auto Entry = SpatialChannelData->mutable_entities()->find(NetGUID);
	if (Entry != SpatialChannelData->mutable_entities()->end())
	{
		bIsRemoved = false;
		return &Entry->second;
	}
	else
	{
		bIsRemoved = true;
		return nullptr;
	}
}

void FTpsSpatialChannelDataProcessor::SetStateToChannelData(const google::protobuf::Message* State,
	google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID)
{
	auto SpatialChannelData = static_cast<unrealpb::SpatialChannelData*>(ChannelData);
	auto Entry = SpatialChannelData->mutable_entities()->find(NetGUID);
	if (Entry != SpatialChannelData->mutable_entities()->end())
	{
		Entry->second.MergeFrom(*State);
	}
	else
	{
		SpatialChannelData->mutable_entities()->insert({ NetGUID, *static_cast<const unrealpb::SpatialEntityState*>(State) });
	}
}

TArray<uint32> FTpsSpatialChannelDataProcessor::GetRelevantNetGUIDsFromChannelData(const google::protobuf::Message* ChannelData)
{
	auto SpatialChannelData = static_cast<const unrealpb::SpatialChannelData*>(ChannelData);
	TArray<uint32> Result;
	for (auto& Pair : SpatialChannelData->entities())
	{
		bool bIgnore = false;
		for (int i = 0; i < Pair.second.objref().context_size(); i++)
		{
			TCHAR* ClassPath = UTF8_TO_TCHAR(Pair.second.objref().context(0).pathname().c_str());
			UClass* EntityClass = LoadObject<UClass>(nullptr, ClassPath);
			
			if (EntityClass == nullptr)
			{
				continue;
			}
			
			if (EntityClass->IsChildOf(APlayerController::StaticClass()) ||
				EntityClass->IsChildOf(APlayerState::StaticClass()))
			{
				bIgnore = true;
				break;;
			}
		}

		if (!bIgnore)
		{
			Result.Add(Pair.first);
		}
	}

	return Result;
}
