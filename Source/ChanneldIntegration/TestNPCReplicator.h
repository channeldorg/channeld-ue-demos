#pragma once

#include "CoreMinimal.h"
#include "tps.pb.h"
#include "Replication/ChanneldReplicatorBase.h"

class CHANNELDINTEGRATION_API FTestNPCReplicator : public FChanneldReplicatorBase_BP
{

public:
	FTestNPCReplicator(UObject* InTargetObj, UClass* InTargetClass);
	virtual ~FTestNPCReplicator() override;

	//~Begin FChanneldReplicatorBase Interface
	virtual google::protobuf::Message* GetDeltaState() override;
	virtual void ClearState() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnStateChanged(const google::protobuf::Message* InNewState) override;
	//~End FChanneldReplicatorBase Interface

private:
	tpspb::TestNPCState* FullState;
	tpspb::TestNPCState* DeltaState;
	bool* bMovingPtr;
	FVector* GoalLocationPtr;
};