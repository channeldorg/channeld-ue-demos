// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChanneldActor.h"
#include "google/protobuf/message.h"
#include "unreal_common.pb.h"
#include "TestRepChanneldActor.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CHANNELDINTEGRATION_API ATestRepChanneldActor : public AChanneldActor
{
	GENERATED_BODY()

protected:
	virtual const unrealpb::SceneComponentState* GetSceneComponentStateFromChannelData(const google::protobuf::Message* ChannelData) override;
	virtual void SetSceneComponentStateToChannelData(unrealpb::SceneComponentState* State, google::protobuf::Message* ChannelData) override;

public:
	virtual google::protobuf::Message* GetChannelDataTemplate() const override;
};
