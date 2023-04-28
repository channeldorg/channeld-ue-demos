#include "TpsChannelDataProcessor.h"
#include "tps.pb.h"
#include "unreal_common.pb.h"
#include "DemoTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

FTpsChannelDataProcessor::FTpsChannelDataProcessor()
{
	RemovedActorState = MakeUnique<unrealpb::ActorState>();
	RemovedActorState->set_removed(true);
	RemovedActorComponentState = MakeUnique<unrealpb::ActorComponentState>();
	RemovedActorComponentState->set_removed(true);
	RemovedSceneComponentState = MakeUnique<unrealpb::SceneComponentState>();
	RemovedSceneComponentState->set_removed(true);
}

bool FTpsChannelDataProcessor::Merge(const google::protobuf::Message* SrcMsg, google::protobuf::Message* DstMsg)
{
	auto Src = static_cast<const tpspb::TestRepChannelData*>(SrcMsg);
	auto Dst = static_cast<tpspb::TestRepChannelData*>(DstMsg);
	
	if (Src->has_gamestate())
	{
		Dst->mutable_gamestate()->MergeFrom(Src->gamestate());
	}
	if (Src->has_testgamestate())
	{
		Dst->mutable_testgamestate()->MergeFrom(Dst->testgamestate());
	}

	for (auto& Pair : Src->pawnstates())
	{
		if (Dst->pawnstates().contains(Pair.first))
		{
			Dst->mutable_pawnstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_pawnstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->characterstates())
	{
		if (Dst->characterstates().contains(Pair.first))
		{
			Dst->mutable_characterstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_characterstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->playerstates())
	{
		if (Dst->playerstates().contains(Pair.first))
		{
			Dst->mutable_playerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_playerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->controllerstates())
	{
		if (Dst->controllerstates().contains(Pair.first))
		{
			Dst->mutable_controllerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_controllerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->playercontrollerstates())
	{
		if (Dst->playercontrollerstates().contains(Pair.first))
		{
			Dst->mutable_playercontrollerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_playercontrollerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->testrepplayercontrollerstates())
	{
		if (Dst->testrepplayercontrollerstates().contains(Pair.first))
		{
			Dst->mutable_testrepplayercontrollerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst->mutable_testrepplayercontrollerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src->scenecomponentstates())
	{
		if (Pair.second.removed())
		{
			Dst->mutable_scenecomponentstates()->erase(Pair.first);
		}
		else
		{
			if (Dst->scenecomponentstates().contains(Pair.first))
			{
				Dst->mutable_scenecomponentstates()->at(Pair.first).MergeFrom(Pair.second);
			}
			else
			{
				Dst->mutable_scenecomponentstates()->emplace(Pair.first, Pair.second);
			}
		}
	}
	
	for (auto& Pair : Src->actorcomponentstates())
	{
		if (Pair.second.removed())
		{
			Dst->mutable_actorcomponentstates()->erase(Pair.first);
		}
		else
		{
			if (Dst->actorcomponentstates().contains(Pair.first))
			{
				Dst->mutable_actorcomponentstates()->at(Pair.first).MergeFrom(Pair.second);
			}
			else
			{
				Dst->mutable_actorcomponentstates()->emplace(Pair.first, Pair.second);
			}
		}
	}

	// Remove the actor and the corresponding states at last, in case any 'parent' state (e.g. CharacterState) is added to the dst above.
	for (auto& Pair : Src->actorstates())
	{
		if (Pair.second.removed())
		{
			Dst->mutable_actorstates()->erase(Pair.first);
			Dst->mutable_pawnstates()->erase(Pair.first);
			Dst->mutable_characterstates()->erase(Pair.first);
			Dst->mutable_controllerstates()->erase(Pair.first);
			Dst->mutable_playercontrollerstates()->erase(Pair.first);
			Dst->mutable_testrepplayercontrollerstates()->erase(Pair.first);
		}
		else
		{
			if (Dst->actorstates().contains(Pair.first))
			{
				Dst->mutable_actorstates()->at(Pair.first).MergeFrom(Pair.second);
			}
			else
			{
				Dst->mutable_actorstates()->emplace(Pair.first, Pair.second);
			}
		}
	}

	return true;
}

const google::protobuf::Message* FTpsChannelDataProcessor::GetStateFromChannelData(google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bIsRemoved)
{
	auto TestRepChannelData = static_cast<tpspb::TestRepChannelData*>(ChannelData);
	if (TargetClass == UObject::StaticClass())
	{
		// Do nothing - just suppress the warning
	}
	else if (TargetClass == AActor::StaticClass())
	{
		auto States = TestRepChannelData->mutable_actorstates();
		if (States->contains(NetGUID))
		{
			auto State = &States->at(NetGUID);
			bIsRemoved = State->removed();
			return State;
		}
	}
	else if (TargetClass == APawn::StaticClass())
	{
		auto States = TestRepChannelData->mutable_pawnstates();
		if (States->contains(NetGUID))
		{
			bIsRemoved = false;
			return &States->at(NetGUID);
		}
	}
	else if (TargetClass == ACharacter::StaticClass())
	{
		auto States = TestRepChannelData->mutable_characterstates();
		if (States->contains(NetGUID))
		{
			bIsRemoved = false;
			return &States->at(NetGUID);
		}
	}
	else if (TargetClass == APlayerState::StaticClass())
	{
		auto States = TestRepChannelData->mutable_playerstates();
		if (States->contains(NetGUID))
		{
			bIsRemoved = false;
			return &States->at(NetGUID);
		}
	}
	else if (TargetClass == AController::StaticClass())
	{
		auto States = TestRepChannelData->mutable_controllerstates();
		if (States->contains(NetGUID))
		{
			bIsRemoved = false;
			return &States->at(NetGUID);
		}
	}
	else if (TargetClass == APlayerController::StaticClass())
	{
		auto States = TestRepChannelData->mutable_playercontrollerstates();
		if (States->contains(NetGUID))
		{
			bIsRemoved = false;
			return &States->at(NetGUID);
		}
	}
	else if (TargetClass == UActorComponent::StaticClass())
	{
		auto States = TestRepChannelData->mutable_actorcomponentstates();
		if (States->contains(NetGUID))
		{
			auto State = &States->at(NetGUID);
			bIsRemoved = State->removed();
			return State;
		}
	}
	else if (TargetClass == USceneComponent::StaticClass())
	{
		auto States = TestRepChannelData->mutable_scenecomponentstates();
		if (States->contains(NetGUID))
		{
			auto State = &States->at(NetGUID);
			bIsRemoved = State->removed();
			return State;
		}
	}
	else if (TargetClass == AGameStateBase::StaticClass())
	{
		bIsRemoved = false;
		return TestRepChannelData->mutable_gamestate();
	}
	else if (TargetClass->GetFName() == FName("BP_RepGameState_C"))
	{
		bIsRemoved = false;
		return TestRepChannelData->mutable_testgamestate();
	}
	else if (TargetClass->GetFName() == FName("BP_TestRepPlayerController_C"))
	{
		auto States = TestRepChannelData->mutable_testrepplayercontrollerstates();
		if (States->contains(NetGUID))
		{
			bIsRemoved = false;
			return &States->at(NetGUID);
		}
	}
	else if (TargetClass->GetFName() == FName("BP_TestNPC_C"))
	{
		auto States = TestRepChannelData->mutable_testnpcstates();
		if (States->contains(NetGUID))
		{
			bIsRemoved = false;
			return &States->at(NetGUID);
		}
	}
	else
	{
		UE_LOG(LogChanneldDemo, Warning, TEXT("State of '%s' is not supported in the ChannelData, NetGUID: %d"), *TargetClass->GetName(), NetGUID);
	}
	
	bIsRemoved = false;
	return nullptr;
}

void FTpsChannelDataProcessor::SetStateToChannelData(const google::protobuf::Message* State, google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID)
{
	auto TestRepChannelData = static_cast<tpspb::TestRepChannelData*>(ChannelData);
	if (TargetClass == UObject::StaticClass())
	{
		// Do nothing - just suppress the warning
	}
	else if (TargetClass == AActor::StaticClass())
	{
		auto ActorState = State ? static_cast<const unrealpb::ActorState*>(State) : RemovedActorState.Get();
		auto States = TestRepChannelData->mutable_actorstates();
		(*States)[NetGUID] = *ActorState;
	}
	else if (TargetClass == APawn::StaticClass())
	{
		auto PawnState = static_cast<const unrealpb::PawnState*>(State);
		if (PawnState)
		{
			auto States = TestRepChannelData->mutable_pawnstates();
			(*States)[NetGUID] = *PawnState;
		}
	}	else if (TargetClass == ACharacter::StaticClass())
	{
		auto CharacterState = static_cast<const unrealpb::CharacterState*>(State);
		if (CharacterState)
		{
			auto States = TestRepChannelData->mutable_characterstates();
			(*States)[NetGUID] = *CharacterState;
		}
	}
	else if (TargetClass == APlayerState::StaticClass())
	{
		auto PlayerState = static_cast<const unrealpb::PlayerState*>(State);
		if (PlayerState)
		{
			auto States = TestRepChannelData->mutable_playerstates();
			(*States)[NetGUID] = *PlayerState;
		}
	}
	else if (TargetClass == AController::StaticClass())
	{
		auto ControllerState = static_cast<const unrealpb::ControllerState*>(State);
		if (ControllerState)
		{
			auto States = TestRepChannelData->mutable_controllerstates();
			(*States)[NetGUID] = *ControllerState;
		}
	}
	else if (TargetClass == APlayerController::StaticClass())
	{
		auto PlayerControllerState = static_cast<const unrealpb::PlayerControllerState*>(State);
		if (PlayerControllerState)
		{
			auto States = TestRepChannelData->mutable_playercontrollerstates();
			(*States)[NetGUID] = *PlayerControllerState;
		}
	}
	else if (TargetClass == UActorComponent::StaticClass())
	{
		auto ActorCompState = State ? static_cast<const unrealpb::ActorComponentState*>(State) : RemovedActorComponentState.Get();
		auto States = TestRepChannelData->mutable_actorcomponentstates();
		(*States)[NetGUID] = *ActorCompState;
	}
	else if (TargetClass == USceneComponent::StaticClass())
	{
		auto SceneCompState = State ? static_cast<const unrealpb::SceneComponentState*>(State) : RemovedSceneComponentState.Get();;
		if (SceneCompState)
		{
			auto States = TestRepChannelData->mutable_scenecomponentstates();
			(*States)[NetGUID] = *SceneCompState;
		}
	}
	else if (TargetClass == AGameStateBase::StaticClass())
	{
		auto GameState = static_cast<const unrealpb::GameStateBase*>(State);
		if (GameState)
		{
			TestRepChannelData->mutable_gamestate()->MergeFrom(*GameState);
		}
	}
	else if (TargetClass->GetFName() == FName("BP_RepGameState_C"))
	{
		auto TestGameState = static_cast<const tpspb::TestRepGameState*>(State);
		if (TestGameState)
		{
			TestRepChannelData->mutable_testgamestate()->MergeFrom(*TestGameState);
		}
	}
	else if (TargetClass->GetFName() == FName("BP_TestRepPlayerController_C"))
	{
		auto TestRepPlayerControllerState = static_cast<const tpspb::TestRepPlayerControllerState*>(State);
		if (TestRepPlayerControllerState)
		{
			auto States = TestRepChannelData->mutable_testrepplayercontrollerstates();
			(*States)[NetGUID] = *TestRepPlayerControllerState;
		}
	}
	else if (TargetClass->GetFName() == FName("BP_TestNPC_C"))
	{
		auto TestNPCState = static_cast<const tpspb::TestNPCState*>(State);
		if (TestNPCState)
		{
			auto States = TestRepChannelData->mutable_testnpcstates();
			(*States)[NetGUID] = *TestNPCState;
		}
	}
	else
	{
		UE_LOG(LogChanneldDemo, Warning, TEXT("State of '%s' is not supported in the ChannelData, NetGUID: %d"), *TargetClass->GetName(), NetGUID);
	}
}
