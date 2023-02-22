#pragma once
#include "TestNPCReplicator.h"
#include "TestRepGameStateReplicator.h"
#include "TestRepPlayerControllerReplicator.h"
#include "Replication/ChanneldReplication.h"
#include "TestReplicatorsRegistration.generated.h"

UCLASS(transient)
class CHANNELDINTEGRATION_API UTestReplicatorsRegistration : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		REGISTER_REPLICATOR_BP_SINGLETON(FTestRepGameStateReplicator, "/Game/Blueprints/BP_RepGameState.BP_RepGameState_C");
		REGISTER_REPLICATOR_BP(FTestRepPlayerControllerReplicator, "/Game/Blueprints/BP_TestRepPlayerController.BP_TestRepPlayerController_C");
		REGISTER_REPLICATOR_BP(FTestNPCReplicator, "/Game/AI/BP_TestNPC.BP_TestNPC_C");
	}
};

