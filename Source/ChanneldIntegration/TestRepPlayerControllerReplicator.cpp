#include "TestRepPlayerControllerReplicator.h"
#include "ChanneldUtils.h"
#include "Net/UnrealNetwork.h"

FTestRepPlayerControllerReplicator::FTestRepPlayerControllerReplicator(UObject* InTargetObj, UClass* InTargetClass)
	: FChanneldReplicatorBase_BP(InTargetObj, InTargetClass)
{
	TArray<FLifetimeProperty> RepProps;
	DisableAllReplicatedPropertiesOfClass(InTargetObj->GetClass(), InTargetClass, EFieldIteratorFlags::ExcludeSuper, RepProps);

	FullState = new tpspb::TestRepPlayerControllerState;
	DeltaState = new tpspb::TestRepPlayerControllerState;
	
	// Prepare Reflection pointers
	{
		auto Property = CastFieldChecked<const FObjectProperty>(InTargetClass->FindPropertyByName(FName("TestRepActor")));
		TestRepActorPtr = Property->ContainerPtrToValuePtr<AActor*>(InTargetObj);
		check(TestRepActorPtr);
	}
}

FTestRepPlayerControllerReplicator::~FTestRepPlayerControllerReplicator()
{
	delete FullState;
	delete DeltaState;
}

google::protobuf::Message* FTestRepPlayerControllerReplicator::GetDeltaState()
{
	return DeltaState;
}

void FTestRepPlayerControllerReplicator::ClearState()
{
	DeltaState->Clear();
	bStateChanged = false;
}

void FTestRepPlayerControllerReplicator::Tick(float DeltaTime)
{
	if (!TargetObject.IsValid())
	{
		return;
	}

	if (*TestRepActorPtr != ChanneldUtils::GetObjectByRef(FullState->mutable_testrepactor(), TargetObject->GetWorld(), false))
	{
		DeltaState->mutable_testrepactor()->CopyFrom(ChanneldUtils::GetRefOfObject(*TestRepActorPtr));
		bStateChanged = true;
	}
	
	if (bStateChanged)
	{
		FullState->MergeFrom(*DeltaState);
	}
}

void FTestRepPlayerControllerReplicator::OnStateChanged(const google::protobuf::Message* InNewState)
{
	if (!TargetObject.IsValid())
	{
		return;
	}
	
	auto NewState = static_cast<const tpspb::TestRepPlayerControllerState*>(InNewState);
	FullState->MergeFrom(*NewState);
	bStateChanged = false;

	if (NewState->has_testrepactor())
	{
		*TestRepActorPtr = Cast<AActor>(ChanneldUtils::GetObjectByRef(&NewState->testrepactor(), TargetObject->GetWorld()));
	}
}

TSharedPtr<google::protobuf::Message> FTestRepPlayerControllerReplicator::SerializeFunctionParams(UFunction* Func, void* Params, bool& bSuccess)
{
	bSuccess = true;
	if (Func->GetFName() == FName("ServerSpawnTestRepActor"))
	{
		return nullptr;
	}
	else if (Func->GetFName() == FName("ServerSpawnCube"))
	{
		return nullptr;
	}
	else if (Func->GetFName() == FName("ServerToggleRotation"))
	{
		return nullptr;
	}

	bSuccess = false;
	return nullptr;
}

TSharedPtr<void> FTestRepPlayerControllerReplicator::DeserializeFunctionParams(UFunction* Func, const std::string& ParamsPayload, bool& bSuccess, bool& bDeferredRPC)
{
	bSuccess = true;
	if (Func->GetFName() == FName("ServerSpawnTestRepActor"))
	{
		return nullptr;
	}
	else if (Func->GetFName() == FName("ServerSpawnCube"))
	{
		return nullptr;
	}
	else if (Func->GetFName() == FName("ServerToggleRotation"))
	{
		return nullptr;
	}

	bSuccess = false;
	return nullptr;
}

