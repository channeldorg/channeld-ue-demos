#include "TestNPCReplicator.h"
#include "ChanneldUtils.h"
#include "Net/UnrealNetwork.h"

FTestNPCReplicator::FTestNPCReplicator(UObject* InTargetObj, UClass* InTargetClass)
: FChanneldReplicatorBase_BP(InTargetObj, InTargetClass)
{
	TArray<FLifetimeProperty> RepProps;
	DisableAllReplicatedPropertiesOfClass(InTargetObj->GetClass(), InTargetClass, EFieldIteratorFlags::ExcludeSuper, RepProps);

	FullState = new tpspb::TestNPCState;
	DeltaState = new tpspb::TestNPCState;
	
	// Prepare Reflection pointers
	{
		auto Property = CastFieldChecked<const FBoolProperty>(InTargetClass->FindPropertyByName(FName("bMoving")));
		bMovingPtr = Property->ContainerPtrToValuePtr<bool>(InTargetObj);
		check(bMovingPtr);
	}
	{
		auto Property = CastFieldChecked<const FStructProperty>(InTargetClass->FindPropertyByName(FName("GoalLocation")));
		GoalLocationPtr = Property->ContainerPtrToValuePtr<FVector>(InTargetObj);
		check(GoalLocationPtr);
	}
}

FTestNPCReplicator::~FTestNPCReplicator()
{
	delete FullState;
	delete DeltaState;
}

google::protobuf::Message* FTestNPCReplicator::GetDeltaState()
{
	return DeltaState;
}

void FTestNPCReplicator::ClearState()
{
	DeltaState->Clear();
	bStateChanged = false;
}

void FTestNPCReplicator::Tick(float DeltaTime)
{
	if (!TargetObject.IsValid())
	{
		return;
	}

	if (*bMovingPtr != FullState->bmoving())
	{
		DeltaState->set_bmoving(*bMovingPtr);
		bStateChanged = true;
	}

	if (ChanneldUtils::CheckDifference(*GoalLocationPtr, FullState->mutable_goallocation()))
	{
		ChanneldUtils::SetVectorToPB(DeltaState->mutable_goallocation(), *GoalLocationPtr, FullState->mutable_goallocation());
		bStateChanged = true;
	}
	
	if (bStateChanged)
	{
		FullState->MergeFrom(*DeltaState);
	}
}

void FTestNPCReplicator::OnStateChanged(const google::protobuf::Message* InNewState)
{
	if (!TargetObject.IsValid())
	{
		return;
	}
	
	auto NewState = static_cast<const tpspb::TestNPCState*>(InNewState);
	FullState->MergeFrom(*NewState);
	bStateChanged = false;

	if (NewState->has_bmoving())
	{
		*bMovingPtr = NewState->bmoving();
	}

	if (NewState->has_goallocation())
	{
		ChanneldUtils::SetVectorFromPB(*GoalLocationPtr, NewState->goallocation());
	}
}
