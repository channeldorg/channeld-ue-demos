#pragma once

#include "CoreMinimal.h"
#include "tps.pb.h"
#include "Replication/ChanneldReplicatorBase.h"

class CHANNELDINTEGRATION_API FTestRepPlayerControllerReplicator : public FChanneldReplicatorBase_BP
{

public:
	FTestRepPlayerControllerReplicator(UObject* InTargetObj);
	virtual ~FTestRepPlayerControllerReplicator() override;

	//~Begin FChanneldReplicatorBase Interface
	virtual google::protobuf::Message* GetDeltaState() override;
	virtual void ClearState() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnStateChanged(const google::protobuf::Message* InNewState) override;
	//~End FChanneldReplicatorBase Interface

	virtual TSharedPtr<google::protobuf::Message> SerializeFunctionParams(UFunction* Func, void* Params, bool& bSuccess) override;
	virtual TSharedPtr<void> DeserializeFunctionParams(UFunction* Func, const std::string& ParamsPayload, bool& bSuccess, bool& bDeferredRPC) override;

private:
	tpspb::TestRepPlayerControllerState* FullState;
	tpspb::TestRepPlayerControllerState* DeltaState;
	AActor** TestRepActorPtr;
};