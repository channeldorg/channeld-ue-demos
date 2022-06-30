// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChanneldNetDriver.h"
#include "Test.pb.h"
#include "UObject/Object.h"
#include "TestProtoMerge.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CHANNELDINTEGRATION_API UTestProtoMerge : public UObject, public IChannelDataProvider
{
	GENERATED_BODY()

public:

	UTestProtoMerge();

	virtual void GetLifetimeReplicatedProps( TArray< class FLifetimeProperty > & OutLifetimeProps ) const override;

	UFUNCTION(BlueprintCallable)
	void SetTestText(const FString& NewValue);

	UFUNCTION(BlueprintCallable)
	void SetTestNum(const int& NewValue);

	virtual void PostLoad() override;
	/* Called when the UE Editor starts up
	virtual void PostInitProperties() override;
	*/

	//virtual void Serialize(FArchive& Ar) override;

	//~ Begin IChannelDataProvider Interface.
	virtual channeld::ChannelType GetChannelType() override {return channeld::GLOBAL;}
	virtual uint32 GetChannelId() override {return ChannelId;}
	virtual void SetChannelId(uint32 ChId) override {ChannelId = ChId;}
	virtual bool UpdateChannelData(google::protobuf::Message* ChannelData) override;
	virtual void OnChannelDataUpdated(const channeld::ChannelDataUpdateMessage* UpdateMsg) override;
	//~ End IChannelDataProvider Interface


private:

	uint32 ChannelId;

	UPROPERTY(Replicated, BlueprintSetter="SetTestText")
	FString TestText;

	UPROPERTY(Replicated, BlueprintSetter="SetTestNum")
	int TestNum;

	channeld::TestChannelDataMessage TestChannelData;

	bool TestChannelDataChanged;

};
