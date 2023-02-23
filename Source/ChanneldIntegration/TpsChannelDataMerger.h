#pragma once
#include "ChannelDataProvider.h"

class FTpsChannelDataMerger : public IChannelDataMerger
{
public:
	virtual bool Merge(const google::protobuf::Message* Src, google::protobuf::Message* Dst) override;
};