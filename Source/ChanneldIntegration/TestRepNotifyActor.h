// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestRepNotifyActor.generated.h"

UCLASS()
class CHANNELDINTEGRATION_API ATestRepNotifyActor : public AActor
{
	GENERATED_BODY()

public:
	ATestRepNotifyActor();

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Health)
	int32 Health;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Aliases)
	TArray<FString> Aliases;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	UFUNCTION()
	void OnRep_Health(int32 OldHealth);

	UFUNCTION()
	void OnRep_Aliases(TArray<FString> OldAliases);
};
