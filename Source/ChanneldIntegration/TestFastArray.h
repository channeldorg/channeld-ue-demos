#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "TestFastArray.generated.h"

/** Step 1: Make your struct inherit from FFastArraySerializerItem */
USTRUCT()
struct FExampleItemEntry : public FFastArraySerializerItem
{
	GENERATED_USTRUCT_BODY()

	// Your data:
	UPROPERTY()
	int32 ExampleIntProperty = 0;
	UPROPERTY()
	float ExampleFloatProperty = 1.0f;
	UPROPERTY()
	UObject* ExampleObjectProperty = nullptr;
	// UPROPERTY()
	// TSoftObjectPtr<USoundBase> ExampleObjRefProperty;
	/** Optional functions you can implement for client side notification of changes to items
	void PreReplicatedRemove();
	void PostReplicatedAdd();
	*/
	void PostReplicatedChange(const FFastArraySerializer& InArraySerializer)
	{
		UE_LOG(LogTemp, Log, TEXT("FExampleItemEntry::PostReplicatedChange: Item changed: %d %f"), ExampleIntProperty, ExampleFloatProperty);
	}
};

/** Step 2: You MUST wrap your TArray in another struct that inherits from FFastArraySerializer */
USTRUCT()
struct FExampleArray: public FFastArraySerializer
{
	GENERATED_USTRUCT_BODY()

	/** Step 4: Copy this, replace example with your names */
	bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms)
	{
		return FastArrayDeltaSerialize<FExampleItemEntry, FExampleArray>(Items, DeltaParms, *this);
	}

	FExampleItemEntry& AddItem(int32 IntProperty, float FloatProperty, UObject* ObjectProperty = nullptr)//, const TSoftObjectPtr<USoundBase>& ObjRefProperty = nullptr)
	{
		FExampleItemEntry NewItem;
		NewItem.ExampleIntProperty = IntProperty;
		NewItem.ExampleFloatProperty = FloatProperty;
		NewItem.ExampleObjectProperty = ObjectProperty;
		// NewItem.ExampleObjRefProperty = ObjRefProperty;
		FExampleItemEntry& Result = Items.Add_GetRef(NewItem);
		MarkArrayDirty();
		return Result;
	}

	void RemoveItemAt(int32 Index)
	{
		Items.RemoveAt(Index);
		MarkArrayDirty();
	}

	void UpdateItemAt(int32 Index, int32 IntProperty, float FloatProperty, UObject* ObjectProperty = nullptr)//, TSoftObjectPtr<USoundBase> ObjRefProperty = nullptr)
	{
		Items[Index].ExampleIntProperty = IntProperty;
		Items[Index].ExampleFloatProperty = FloatProperty;
		Items[Index].ExampleObjectProperty = ObjectProperty;
		// Items[Index].ExampleObjRefProperty = ObjRefProperty;
		MarkItemDirty(Items[Index]);
	}

	void EmptyItems()
	{
		Items.Empty();
		MarkArrayDirty();
	}

	void GetItem(int32 Index, int32& IntProperty, float& FloatProperty, UObject*& ObjectProperty/*, TSoftObjectPtr<USoundBase>& ObjRefProperty*/) const
	{
		IntProperty = Items[Index].ExampleIntProperty;
		FloatProperty = Items[Index].ExampleFloatProperty;
		ObjectProperty = Items[Index].ExampleObjectProperty;
		// ObjRefProperty = Items[Index].ExampleObjRefProperty;
	}

	int32 Num() const
	{
		return Items.Num();
	}

private:
		
	UPROPERTY()
	TArray<FExampleItemEntry> Items; /** Step 3: You MUST have a TArray named Items of the struct you made in step 1. */

};

/** Step 5: Copy and paste this struct trait, replacing FExampleArray with your Step 2 struct. */
template<>
struct TStructOpsTypeTraits< FExampleArray > : public TStructOpsTypeTraitsBase2< FExampleArray >
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};

UCLASS(BlueprintType)
class CHANNELDINTEGRATION_API ATestFastArrayActor : public AActor
{
	GENERATED_BODY()

public:

	ATestFastArrayActor(const FObjectInitializer& ObjectInitializer);
	
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing = OnRep_ExampleArray)
	FExampleArray ExampleArray;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetNumItems() const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetItem(int32 Index, int32& IntProperty, float& FloatProperty, UObject*& ObjectProperty/*, TSoftObjectPtr<USoundBase>& ObjRefProperty*/) const;

	UFUNCTION(Server, Reliable, BlueprintCallable, meta=(AutoCreateRefTerm="ObjRefProperty"))
	void ServerAddItem(int32 IntProperty, float FloatProperty, UObject* ObjectProperty = nullptr);//, const TSoftObjectPtr<USoundBase>& ObjRefProperty = nullptr);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerRemoveItemAt(int32 Index);

	UFUNCTION(Server, Reliable, BlueprintCallable, meta=(AutoCreateRefTerm="ObjRefProperty"))
	void ServerUpdateItemAt(int32 Index, int32 IntProperty, float FloatProperty, UObject* ObjectProperty = nullptr);//, const TSoftObjectPtr<USoundBase>& ObjRefProperty = nullptr);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerEmptyItems();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_ExampleArray();
};