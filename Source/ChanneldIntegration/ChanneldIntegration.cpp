// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChanneldIntegration.h"
#include "Modules/ModuleManager.h"
#include "ChanneldUE/Replication/ChanneldReplication.h"
#include "TestRepPlayerControllerReplicator.h"

//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ChanneldIntegration, "ChanneldIntegration" );

void FChanneldIntegrationModule::StartupModule()
{
	REGISTER_REPLICATOR_BP(FTestRepPlayerControllerReplicator, "/Game/Blueprints/BP_TestRepPlayerController.BP_TestRepPlayerController_C");
}

void FChanneldIntegrationModule::ShutdownModule()
{

}

IMPLEMENT_PRIMARY_GAME_MODULE(FChanneldIntegrationModule, ChanneldIntegration, "ChanneldIntegration");
