// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Replication/ChanneldReplicationComponent.h"
#include "GameStateRepComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, meta = (DisplayName = "GameStateBase Replication", BlueprintSpawnableComponent))
class CHANNELDINTEGRATION_API UGameStateRepComponent : public UChanneldReplicationComponent
{
	GENERATED_BODY()

public:
	UGameStateRepComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual const google::protobuf::Message* GetStateFromChannelData(google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bRemoved) override;
	virtual void SetStateToChannelData(const google::protobuf::Message* State, google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID) override;
};
