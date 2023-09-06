#pragma once
#include "CoreMinimal.h"

#include "TestFastArray.generated.h"

USTRUCT()
struct FTestFastArrayItem : public FFastArraySerializerItem
{
	GENERATED_BODY()

	UPROPERTY()
	int32 IntValue;

	UPROPERTY()
	FString StringValue;

	FTestFastArrayItem(int32 InIntValue = 0, const FString& InStringValue = TEXT(""))
		: IntValue(InIntValue)
		, StringValue(InStringValue)
	{
	}
};

USTRUCT()
struct FTestFastArray : public FFastArraySerializer
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FTestFastArrayItem> Items;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParam)
	{
		return FastArrayDeltaSerialize<FTestFastArrayItem>(Items, DeltaParam, *this);
	}
};

template<>
struct TStructOpsTypeTraits<FTestFastArray> : public TStructOpsTypeTraitsBase2<FTestFastArray>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};