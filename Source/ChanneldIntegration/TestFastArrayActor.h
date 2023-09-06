#pragma once
#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "TestFastArray.h"

#include "TestFastArrayActor.generated.h"

UCLASS(Blueprintable)
class CHANNELDINTEGRATION_API ATestFastArrayActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_TestFastArray)
	FTestFastArray TestFastArray;

	UFUNCTION(BlueprintCallable)
	void AddTestFastArrayItem(int32 InIntValue, const FString& InStringValue)
	{
		TestFastArray.Items.Add(FTestFastArrayItem(InIntValue, InStringValue));
		TestFastArray.MarkArrayDirty();
	}

	UFUNCTION(BlueprintCallable)
	void RemoveTestFastArrayItem(int32 Index)
	{
		TestFastArray.Items.RemoveAt(Index);
		TestFastArray.MarkArrayDirty();
	}

	UFUNCTION(BlueprintCallable)
	void UpdateTestFastArrayItem(int32 Index, int32 NewIntValue, const FString& NewStringValue)
	{
		auto& Item = TestFastArray.Items[Index];
		Item.IntValue = NewIntValue;
		Item.StringValue = NewStringValue;
		TestFastArray.MarkItemDirty(Item);
	}

	UFUNCTION(BlueprintCallable)
	int32 GetTestFastArrayLength() const
	{
		return TestFastArray.Items.Num();
	}
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_TestFastArray();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		DOREPLIFETIME(ATestFastArrayActor, TestFastArray);
	}	
};
