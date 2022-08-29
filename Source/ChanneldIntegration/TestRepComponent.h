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
	virtual const unrealpb::SceneComponentState* GetSceneComponentStateFromChannelData(google::protobuf::Message* ChannelData, uint32 NetGUID) override;
	virtual void SetSceneComponentStateToChannelData(unrealpb::SceneComponentState* State, google::protobuf::Message* ChannelData, uint32 NetGUID) override;

public:
	virtual google::protobuf::Message* GetChannelDataTemplate() const override;
};
