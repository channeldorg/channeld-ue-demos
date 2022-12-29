#pragma once

#include "CoreMinimal.h"
#include "tps.pb.h"
#include "Replication/ChanneldReplicatorBase.h"

class CHANNELDINTEGRATION_API FTestRepGameStateReplicator : public FChanneldReplicatorBase_BP
{

public:
	FTestRepGameStateReplicator(UObject* InTargetObj, UClass* InTargetClass);
	virtual ~FTestRepGameStateReplicator() override;

	//~Begin FChanneldReplicatorBase Interface
	virtual uint32 GetNetGUID() override;
	virtual google::protobuf::Message* GetDeltaState() override;
	virtual void ClearState() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnStateChanged(const google::protobuf::Message* InNewState) override;
	//~End FChanneldReplicatorBase Interface

	virtual TSharedPtr<google::protobuf::Message> SerializeFunctionParams(UFunction* Func, void* Params, bool& bSuccess) override;
	virtual TSharedPtr<void> DeserializeFunctionParams(UFunction* Func, const std::string& ParamsPayload, bool& bSuccess, bool& bDelayRPC) override;

protected:
	tpspb::TestRepGameState* FullState;
	tpspb::TestRepGameState* DeltaState;

private:
	int* JumpsPtr;
	UFunction* OnRep_JumpsFunc;
};