#include "TpsEntityChannelDataProcessor.h"

#include "ChanneldUtils.h"
#include "tps.pb.h"
#include "DemoTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

bool FTpsEntityChannelDataProcessor::Merge(const google::protobuf::Message* SrcMsg, google::protobuf::Message* DstMsg)
{
	DstMsg->MergeFrom(*SrcMsg);
	return true;
}

bool FTpsEntityChannelDataProcessor::UpdateChannelData(UObject* TargetObj, google::protobuf::Message* ChannelData)
{
	/* By now, the NetId should has already been assigned (in UChanneldNetDriver::OnServerSpawnedActor), so the 
	 * condition below would never match.
	// EntityChannelData.ObjRef should only be set once, from the Spawn message.
	if (!ChanneldUtils::GetNetId(TargetObj, false).IsValid())
	{
		const auto EntityChannelData = static_cast<tpspb::EntityChannelData*>(ChannelData);
		if (!EntityChannelData->has_objref())
		{
			EntityChannelData->mutable_objref()->CopyFrom(*ChanneldUtils::GetRefOfObject(TargetObj, nullptr, true));
		}
	}
	*/
	return true;
}

const google::protobuf::Message* FTpsEntityChannelDataProcessor::GetStateFromChannelData(
	google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bIsRemoved)
{
	bIsRemoved = false;
	auto EntityChannelData = static_cast<tpspb::EntityChannelData*>(ChannelData);
	if (TargetClass == UObject::StaticClass())
	{
		return EntityChannelData->has_objref() ? &EntityChannelData->objref() : nullptr;
	}
	else if (TargetClass == AActor::StaticClass())
	{
		return EntityChannelData->has_actorstate() ? &EntityChannelData->actorstate() : nullptr;
	}
	else if (TargetClass == APawn::StaticClass())
	{
		return EntityChannelData->has_pawnstate() ? &EntityChannelData->pawnstate() : nullptr;
	}
	else if (TargetClass == ACharacter::StaticClass())
	{
		return EntityChannelData->has_characterstate() ? &EntityChannelData->characterstate() : nullptr;
	}
	else if (TargetClass == APlayerState::StaticClass())
	{
		return EntityChannelData->has_playerstate() ? &EntityChannelData->playerstate() : nullptr;
	}
	else if (TargetClass == AController::StaticClass())
	{
		return EntityChannelData->has_controllerstate() ? &EntityChannelData->controllerstate() : nullptr;
	}
	else if (TargetClass == APlayerController::StaticClass())
	{
		return EntityChannelData->has_playercontrollerstate() ? &EntityChannelData->playercontrollerstate() : nullptr;
	}
	else if (TargetClass == UActorComponent::StaticClass())
	{
		return EntityChannelData->has_actorcomponentstate() ? &EntityChannelData->actorcomponentstate() : nullptr;
	}
	else if (TargetClass == USceneComponent::StaticClass())
	{
		return EntityChannelData->has_scenecomponentstate() ? &EntityChannelData->scenecomponentstate() : nullptr;
	}
	else if (TargetClass->GetFName() == FName("BP_TestRepPlayerController_C"))
	{
		return EntityChannelData->has_testrepplayercontrollerstate() ? &EntityChannelData->testrepplayercontrollerstate() : nullptr;
	}
	else if (TargetClass->GetFName() == FName("BP_TestNPC_C"))
	{
		return EntityChannelData->has_testnpcstate() ? &EntityChannelData->testnpcstate() : nullptr;
	}
	else
	{
		UE_LOG(LogChanneldDemo, Warning, TEXT("State of '%s' is not supported in the ChannelData, NetGUID: %d"), *TargetClass->GetName(), NetGUID);
	}
	
	return nullptr;
}

void FTpsEntityChannelDataProcessor::SetStateToChannelData(const google::protobuf::Message* State,
	google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID)
{
	if (State == nullptr)
	{
		return;
	}
	
	auto EntityChannelData = static_cast<tpspb::EntityChannelData*>(ChannelData);
	if (TargetClass == UObject::StaticClass())
	{
		EntityChannelData->mutable_objref()->CopyFrom(*State);
	}
	else if (TargetClass == AActor::StaticClass())
	{
		EntityChannelData->mutable_actorstate()->CopyFrom(*State);
	}
	else if (TargetClass == APawn::StaticClass())
	{
		EntityChannelData->mutable_pawnstate()->CopyFrom(*State);
	}
	else if (TargetClass == ACharacter::StaticClass())
	{
		EntityChannelData->mutable_characterstate()->CopyFrom(*State);
	}
	else if (TargetClass == APlayerState::StaticClass())
	{
		EntityChannelData->mutable_playerstate()->CopyFrom(*State);
	}
	else if (TargetClass == AController::StaticClass())
	{
		EntityChannelData->mutable_controllerstate()->CopyFrom(*State);
	}
	else if (TargetClass == APlayerController::StaticClass())
	{
		EntityChannelData->mutable_playercontrollerstate()->CopyFrom(*State);
	}
	else if (TargetClass == UActorComponent::StaticClass())
	{
		EntityChannelData->mutable_actorcomponentstate()->CopyFrom(*State);
	}
	else if (TargetClass == USceneComponent::StaticClass())
	{
		EntityChannelData->mutable_scenecomponentstate()->CopyFrom(*State);
	}
	else if (TargetClass->GetFName() == FName("BP_TestRepPlayerController_C"))
	{
		EntityChannelData->mutable_testrepplayercontrollerstate()->CopyFrom(*State);
	}
	else if (TargetClass->GetFName() == FName("BP_TestNPC_C"))
	{
		EntityChannelData->mutable_testnpcstate()->CopyFrom(*State);
	}
	else
	{
		UE_LOG(LogChanneldDemo, Warning, TEXT("State of '%s' is not supported in the ChannelData, NetGUID: %d"), *TargetClass->GetName(), NetGUID);
	}
}
