#include "ChanneldIntegration.h"

#include "Modules/ModuleManager.h"
#include "ChanneldUE/Replication/ChanneldReplication.h"
// #include "TestRepGameStateReplicator.h"
// #include "TestRepPlayerControllerReplicator.h"
// #include "TestNPCReplicator.h"

//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ChanneldIntegration, "ChanneldIntegration" );

void FChanneldIntegrationModule::StartupModule()
{
	/* We need to move the registration of the replicators in the game module to an engine subsystem, as the registration
	 * should happen after the FChanneldUEModule::StartupModule(), so the field indices can match the proto.
	 * 
	REGISTER_REPLICATOR_BP_SINGLETON(FTestRepGameStateReplicator, "/Game/Blueprints/BP_RepGameState.BP_RepGameState_C");
	REGISTER_REPLICATOR_BP(FTestRepPlayerControllerReplicator, "/Game/Blueprints/BP_TestRepPlayerController.BP_TestRepPlayerController_C");
	REGISTER_REPLICATOR_BP(FTestNPCReplicator, "/Game/AI/BP_TestNPC.BP_TestNPC_C");
	*/

	TpsChannelDataProcessor = new FTpsChannelDataProcessor();
	ChanneldReplication::RegisterChannelDataProcessor(TEXT("tpspb.TestRepChannelData"), TpsChannelDataProcessor);

	SpatialChannelDataProcessor = new FTpsSpatialChannelDataProcessor();
	ChanneldReplication::RegisterChannelDataProcessor(TEXT("unrealpb.SpatialChannelData"), SpatialChannelDataProcessor);
	
	EntityChannelDataProcessor = new FTpsEntityChannelDataProcessor();
	ChanneldReplication::RegisterChannelDataProcessor(TEXT("tpspb.EntityChannelData"), EntityChannelDataProcessor);
}

void FChanneldIntegrationModule::ShutdownModule()
{
	delete TpsChannelDataProcessor;
	delete EntityChannelDataProcessor;
}

IMPLEMENT_PRIMARY_GAME_MODULE(FChanneldIntegrationModule, ChanneldIntegration, "ChanneldIntegration");
