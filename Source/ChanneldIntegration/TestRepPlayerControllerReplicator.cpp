#include "TestRepPlayerControllerReplicator.h"

FTestRepPlayerControllerReplicator::FTestRepPlayerControllerReplicator(UObject* InTargetObj, UClass* InTargetClass)
	: FChanneldReplicatorBase_BP(InTargetObj, InTargetClass)
{

}

FTestRepPlayerControllerReplicator::~FTestRepPlayerControllerReplicator()
{

}

google::protobuf::Message* FTestRepPlayerControllerReplicator::GetDeltaState()
{
	return nullptr;
}

void FTestRepPlayerControllerReplicator::ClearState()
{

}

void FTestRepPlayerControllerReplicator::Tick(float DeltaTime)
{

}

void FTestRepPlayerControllerReplicator::OnStateChanged(const google::protobuf::Message* NewState)
{

}

TSharedPtr<google::protobuf::Message> FTestRepPlayerControllerReplicator::SerializeFunctionParams(UFunction* Func, void* Params, bool& bSuccess)
{
	bSuccess = true;
	if (Func->GetFName() == FName("ServerSpawnTestRepActor"))
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

void* FTestRepPlayerControllerReplicator::DeserializeFunctionParams(UFunction* Func, const std::string& ParamsPayload, bool& bSuccess, bool& bDelayRPC)
{
	bSuccess = true;
	if (Func->GetFName() == FName("ServerSpawnTestRepActor"))
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

