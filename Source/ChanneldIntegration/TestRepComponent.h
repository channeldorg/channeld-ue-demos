// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Replication/ChanneldReplicationComponent.h"
#include "TestRepComponent.generated.h"

DECLARE_LOG_CATEGORY_CLASS(LogChanneldTest, Log, All);
/**
 * 
 */
UCLASS(BlueprintType, meta = (DisplayName = "Channeld Test Replication Component", BlueprintSpawnableComponent))
class CHANNELDINTEGRATION_API UTestRepComponent : public UChanneldReplicationComponent
{
	GENERATED_BODY()

public:
	UTestRepComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	// virtual google::protobuf::Message* GetChannelDataTemplate() const override;

protected:
	virtual const google::protobuf::Message* GetStateFromChannelData(google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bRemoved) override;
	virtual void SetStateToChannelData(const google::protobuf::Message* State, google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID) override;

private:
	TUniquePtr<unrealpb::ActorState> RemovedActorState;
	TUniquePtr<unrealpb::ActorComponentState> RemovedActorComponentState;
};
