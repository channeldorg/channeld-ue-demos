#include "TestFastArray.h"

ATestFastArrayActor::ATestFastArrayActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATestFastArrayActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATestFastArrayActor, ExampleArray);
}

int32 ATestFastArrayActor::GetNumItems() const
{
	return ExampleArray.Num();
}

void ATestFastArrayActor::GetItem(int32 Index, int32& IntProperty, float& FloatProperty, UObject*& ObjectProperty/*, TSoftObjectPtr<USoundBase>& ObjRefProperty*/) const
{
	ExampleArray.GetItem(Index, IntProperty, FloatProperty, ObjectProperty);
}

void ATestFastArrayActor::ServerAddItem_Implementation(int32 IntProperty, float FloatProperty, UObject* ObjectProperty)//, const TSoftObjectPtr<USoundBase>& ObjRefProperty)
{
	ExampleArray.AddItem(IntProperty, FloatProperty, ObjectProperty);
}

void ATestFastArrayActor::ServerRemoveItemAt_Implementation(int32 Index)
{
	ExampleArray.RemoveItemAt(Index);
}

void ATestFastArrayActor::ServerUpdateItemAt_Implementation(int32 Index, int32 IntProperty, float FloatProperty, UObject* ObjectProperty)//, const TSoftObjectPtr<USoundBase>& ObjRefProperty)
{
	ExampleArray.UpdateItemAt(Index, IntProperty, FloatProperty, ObjectProperty);
}

void ATestFastArrayActor::ServerEmptyItems_Implementation()
{
	ExampleArray.EmptyItems();
}

