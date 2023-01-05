#include "TestRepGameStateReplicator.h"

#include "tps.pb.h"
#include "Net/UnrealNetwork.h"

FTestRepGameStateReplicator::FTestRepGameStateReplicator(UObject* InTargetObj, UClass* InTargetClass)
	: FChanneldReplicatorBase_BP(InTargetObj, InTargetClass)
{
	TArray<FLifetimeProperty> RepProps;
	DisableAllReplicatedPropertiesOfClass(InTargetObj->GetClass(), InTargetClass, EFieldIteratorFlags::ExcludeSuper, RepProps);

	FullState = new tpspb::TestRepGameState;
	DeltaState = new tpspb::TestRepGameState;

	// Prepare Reflection pointers
	{
		auto Property = CastFieldChecked<const FIntProperty>(InTargetClass->FindPropertyByName(FName("Jumps")));
		JumpsPtr = Property->ContainerPtrToValuePtr<int32>(InTargetObj);
		check(JumpsPtr);
	}
	OnRep_JumpsFunc = InTargetClass->FindFunctionByName(FName("OnRep_Jumps"));
	check(OnRep_JumpsFunc);

}

FTestRepGameStateReplicator::~FTestRepGameStateReplicator()
{
	delete FullState;
	delete DeltaState;
}

uint32 FTestRepGameStateReplicator::GetNetGUID()
{
	// GameState doesn't have a valid NetGUID, so let's use a constant value.
	return GameStateNetId;
}

google::protobuf::Message* FTestRepGameStateReplicator::GetDeltaState()
{
	return DeltaState;
}

void FTestRepGameStateReplicator::ClearState()
{
	DeltaState->Clear();
	bStateChanged = false;
}

void FTestRepGameStateReplicator::Tick(float DeltaTime)
{
	if (!TargetObject.IsValid())
	{
		return;
	}

	if (!Cast<AActor>(TargetObject.Get())->HasAuthority())
	{
		return;
	}

	if (*JumpsPtr != FullState->jumps())
	{
		DeltaState->set_jumps(*JumpsPtr);
		FullState->set_jumps(*JumpsPtr);
		bStateChanged = true;
	}
}

void FTestRepGameStateReplicator::OnStateChanged(const google::protobuf::Message* InNewState)
{
	if (!TargetObject.IsValid())
	{
		return;
	}

	if (Cast<AActor>(TargetObject.Get())->HasAuthority())
	{
		return;
	}

	auto NewState = static_cast<const tpspb::TestRepGameState*>(InNewState);
	FullState->MergeFrom(*NewState);
	bStateChanged = false;

	if (NewState->has_jumps())
	{
		*JumpsPtr = NewState->jumps();
		TargetObject->ProcessEvent(OnRep_JumpsFunc, NULL);
	}
}

TSharedPtr<google::protobuf::Message> FTestRepGameStateReplicator::SerializeFunctionParams(UFunction* Func, void* Params, bool& bSuccess)
{
	bSuccess = true;
	if (Func->GetFName() == FName("AddJumps"))
	{
		return nullptr;
	}

	bSuccess = false;
	return nullptr;
}

TSharedPtr<void> FTestRepGameStateReplicator::DeserializeFunctionParams(UFunction* Func, const std::string& ParamsPayload, bool& bSuccess, bool& bDelayRPC)
{
	bSuccess = true;
	if (Func->GetFName() == FName("AddJumps"))
	{
		return nullptr;
	}

	bSuccess = false;
	return nullptr;
}

