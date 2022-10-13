// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Replication/ChanneldReplicationComponent.h"
#include "TestRepComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, meta = (DisplayName = "Test Replication", BlueprintSpawnableComponent))
class CHANNELDINTEGRATION_API UTestRepComponent : public UChanneldReplicationComponent
{
	GENERATED_BODY()

protected:
	virtual const google::protobuf::Message* GetStateFromChannelData(google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bRemoved) override;
	virtual void SetStateToChannelData(const google::protobuf::Message* State, google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID) override;

public:
	virtual google::protobuf::Message* GetChannelDataTemplate() const override;
};
