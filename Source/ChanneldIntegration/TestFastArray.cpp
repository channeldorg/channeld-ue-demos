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

void ATestFastArrayActor::GetItem(int32 Index, int32& IntProperty, float& FloatProperty)
{
	ExampleArray.GetItem(Index, IntProperty, FloatProperty);
}

void ATestFastArrayActor::ServerAddItem_Implementation(int32 IntProperty, float FloatProperty)
{
	ExampleArray.AddItem(IntProperty, FloatProperty);
}

void ATestFastArrayActor::ServerRemoveItemAt_Implementation(int32 Index)
{
	ExampleArray.RemoveItemAt(Index);
}

void ATestFastArrayActor::ServerUpdateItemAt_Implementation(int32 Index, int32 IntProperty, float FloatProperty)
{
	ExampleArray.UpdateItemAt(Index, IntProperty, FloatProperty);
}

void ATestFastArrayActor::ServerEmptyItems_Implementation()
{
	ExampleArray.EmptyItems();
}

