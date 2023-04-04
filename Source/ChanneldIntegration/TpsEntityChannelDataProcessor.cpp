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
	/* EntityChannelData.ObjRef should only be set once, from the Spawn message.
	const auto EntityChannelData = static_cast<tpspb::EntityChannelData*>(ChannelData);
	if (!EntityChannelData->has_objref())
	{
		EntityChannelData->mutable_objref()->CopyFrom(*ChanneldUtils::GetRefOfObject(TargetObj));
	}
	*/
	return true;
}

const google::protobuf::Message* FTpsEntityChannelDataProcessor::GetStateFromChannelData(
	google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bIsRemoved)
{
	bIsRemoved = false;
	auto EntityChannelData = static_cast<tpspb::EntityChannelData*>(ChannelData);
	if (TargetClass == AActor::StaticClass())
	{
		return EntityChannelData->mutable_actorstate();
	}
	else if (TargetClass == APawn::StaticClass())
	{
		return EntityChannelData->mutable_pawnstate();
	}
	else if (TargetClass == ACharacter::StaticClass())
	{
		return EntityChannelData->mutable_characterstate();
	}
	else if (TargetClass == APlayerState::StaticClass())
	{
		return EntityChannelData->mutable_playerstate();
	}
	else if (TargetClass == AController::StaticClass())
	{
		return EntityChannelData->mutable_controllerstate();
	}
	else if (TargetClass == APlayerController::StaticClass())
	{
		return EntityChannelData->mutable_playercontrollerstate();
	}
	else if (TargetClass == UActorComponent::StaticClass())
	{
		return EntityChannelData->mutable_actorcomponentstate();
	}
	else if (TargetClass == USceneComponent::StaticClass())
	{
		return EntityChannelData->mutable_scenecomponentstate();
	}
	else if (TargetClass->GetFName() == FName("BP_TestRepPlayerController_C"))
	{
		return EntityChannelData->mutable_testrepplayercontrollerstate();
	}
	else if (TargetClass->GetFName() == FName("BP_TestNPC_C"))
	{
		return EntityChannelData->mutable_testnpcstate();
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
	if (TargetClass == AActor::StaticClass())
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

TArray<uint32> FTpsEntityChannelDataProcessor::GetRelevantNetGUIDsFromChannelData(
	const google::protobuf::Message* ChannelData)
{
	// Entity channels are subscribed after spawn, so the NetId should already been resolved. 
	// auto EntityChannelData = static_cast<const tpspb::EntityChannelData*>(ChannelData);

	static const TArray<uint32> EmptyArray;
	return EmptyArray;
}
