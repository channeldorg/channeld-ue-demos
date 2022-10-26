// Fill out your copyright notice in the Description page of Project Settings.


#include "TestRepComponent.h"
#include "tps.pb.h"
#include "unreal_common.pb.h"
#include "ChanneldUE/ChanneldTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

const google::protobuf::Message* UTestRepComponent::GetStateFromChannelData(google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID, bool& bIsRemoved)
{
	auto TestRepChannelData = static_cast<tpspb::TestRepChannelData*>(ChannelData);
	if (TargetClass == AActor::StaticClass())
	{
		auto States = TestRepChannelData->mutable_actorstates();
		if (States->contains(NetGUID))
		{
			auto State = &States->at(NetGUID);
			bIsRemoved = State->removed();
			return State;
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
			bIsRemoved = false;
			return &States->at(NetGUID);
		}
	}
	else if (TargetClass == AGameStateBase::StaticClass())
	{
		bIsRemoved = false;
		return TestRepChannelData->mutable_gamestate();
	}
	else if (TargetClass->GetFName() == FName("BP_TestRepPlayerController_C"))
	{
		return nullptr;
	}
	else
	{
		UE_LOG(LogChanneldTest, Warning, TEXT("State of '%s' is not supported in the ChannelData, NetGUID: %d"), *TargetClass->GetName(), NetGUID);
	}
	
	bIsRemoved = false;
	return nullptr;
}

void UTestRepComponent::SetStateToChannelData(const google::protobuf::Message* State, google::protobuf::Message* ChannelData, UClass* TargetClass, uint32 NetGUID)
{
	auto TestRepChannelData = static_cast<tpspb::TestRepChannelData*>(ChannelData);
	if (TargetClass == AActor::StaticClass())
	{
		auto ActorState = static_cast<const unrealpb::ActorState*>(State);
		auto States = TestRepChannelData->mutable_actorstates();
		(*States)[NetGUID] = *ActorState;
	}
	else if (TargetClass == ACharacter::StaticClass())
	{
		auto CharacterState = static_cast<const unrealpb::CharacterState*>(State);
		auto States = TestRepChannelData->mutable_characterstates();
		(*States)[NetGUID] = *CharacterState;
	}
	else if (TargetClass == APlayerState::StaticClass())
	{
		auto PlayerState = static_cast<const unrealpb::PlayerState*>(State);
		auto States = TestRepChannelData->mutable_playerstates();
		(*States)[NetGUID] = *PlayerState;
	}
	else if (TargetClass == AController::StaticClass())
	{
		auto ControllerState = static_cast<const unrealpb::ControllerState*>(State);
		auto States = TestRepChannelData->mutable_controllerstates();
		(*States)[NetGUID] = *ControllerState;
	}
	else if (TargetClass == APlayerController::StaticClass())
	{
		auto PlayerControllerState = static_cast<const unrealpb::PlayerControllerState*>(State);
		auto States = TestRepChannelData->mutable_playercontrollerstates();
		(*States)[NetGUID] = *PlayerControllerState;
	}
	else if (TargetClass == UActorComponent::StaticClass())
	{
		auto ActorCompState = static_cast<const unrealpb::ActorComponentState*>(State);
		auto States = TestRepChannelData->mutable_actorcomponentstates();
		(*States)[NetGUID] = *ActorCompState;
	}
	else if (TargetClass == USceneComponent::StaticClass())
	{
		auto SceneCompState = static_cast<const unrealpb::SceneComponentState*>(State);
		auto States = TestRepChannelData->mutable_scenecomponentstates();
		(*States)[NetGUID] = *SceneCompState;
	}
	else if (TargetClass == AGameStateBase::StaticClass())
	{
		auto GameState = static_cast<const unrealpb::GameStateBase*>(State);
		TestRepChannelData->mutable_gamestate()->MergeFrom(*GameState);
	}
	else if (TargetClass->GetFName() == FName("BP_TestRepPlayerController_C"))
	{
	}
	else
	{
		UE_LOG(LogChanneldTest, Warning, TEXT("State of '%s' is not supported in the ChannelData, NetGUID: %d"), *TargetClass->GetName(), NetGUID);
	}
}

google::protobuf::Message* UTestRepComponent::GetChannelDataTemplate() const
{
	return new tpspb::TestRepChannelData;
}