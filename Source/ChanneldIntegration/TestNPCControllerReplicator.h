#pragma once

#include "CoreMinimal.h"
#include "tps.pb.h"
#include "Replication/ChanneldReplicatorBase.h"

class CHANNELDINTEGRATION_API FTestNPCControllerReplicator : public FChanneldReplicatorBase_BP
{

public:
	FTestNPCControllerReplicator(UObject* InTargetObj, UClass* InTargetClass);
	virtual ~FTestNPCControllerReplicator() override;

	//~Begin FChanneldReplicatorBase Interface
	virtual google::protobuf::Message* GetDeltaState() override;
	virtual void ClearState() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnStateChanged(const google::protobuf::Message* InNewState) override;
	//~End FChanneldReplicatorBase Interface

private:
	tpspb::TestNPCControllerState* FullState;
	tpspb::TestNPCControllerState* DeltaState;
	bool* bMovingPtr;
	FVector* GoalLocationPtr;
};