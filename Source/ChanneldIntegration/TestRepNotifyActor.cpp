// Fill out your copyright notice in the Description page of Project Settings.


#include "TestRepNotifyActor.h"

#include "Net/UnrealNetwork.h"

// Sets default values
ATestRepNotifyActor::ATestRepNotifyActor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATestRepNotifyActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATestRepNotifyActor, Health);
	DOREPLIFETIME(ATestRepNotifyActor, Aliases);
}

void ATestRepNotifyActor::OnRep_Health(int32 OldHealth)
{
	UE_LOG(LogTemp, Warning, TEXT("Health changed from %d to %d"), OldHealth, Health);
}

void ATestRepNotifyActor::OnRep_Aliases(TArray<FString> OldAliases)
{
	UE_LOG(LogTemp, Warning, TEXT("Aliases changed to from %s to %s"), *FString::Join(OldAliases, TEXT(",")), *FString::Join(Aliases, TEXT(",")));
}

