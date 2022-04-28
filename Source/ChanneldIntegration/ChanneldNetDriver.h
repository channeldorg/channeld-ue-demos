// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChanneldTypes.h"
#include "Engine/NetDriver.h"
#include "IpNetDriver.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Test.pb.h"
#include "google/protobuf/message.h"
#include "ChanneldNetDriver.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogChanneld, Log, All);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FChanneldMessageDelegate, UChanneldClient*, uint32, const google::protobuf::Message*)

class IChannelDataProvider
{
public:
	virtual bool UpdateChannelData(google::protobuf::Message& ChannelData) = 0;
	virtual void OnChannelDataUpdated(const ChannelId ChId, const google::protobuf::Message& ChannelData) = 0;
	virtual ~IChannelDataProvider() {}
};

UCLASS()
class CHANNELDINTEGRATION_API UChanneldClient : public UObject
{
	GENERATED_BODY()

};

/**
 * 
 */
UCLASS(transient, config=Engine)
class CHANNELDINTEGRATION_API UChanneldNetDriver : public UIpNetDriver
{
	GENERATED_BODY()

public:

	// Constructors.
	UChanneldNetDriver(const FObjectInitializer& ObjectInitializer);

	//~ Begin UObject Interface
	virtual void PostInitProperties() override;
	//~ End UObject Interface

	//~ Begin UNetDriver Interface.
	virtual void Shutdown() override;
	virtual bool IsAvailable() const override;
	virtual bool InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL, bool bReuseAddressAndPort, FString& Error) override;
	virtual bool InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error) override;
	virtual bool InitListen(FNetworkNotify* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error) override;
	virtual void TickDispatch(float DeltaTime) override;

	virtual class ISocketSubsystem* GetSocketSubsystem() override;
	virtual FUniqueSocket CreateSocketForProtocol(const FName& ProtocolType) override;
	virtual FUniqueSocket CreateAndBindSocket(TSharedRef<FInternetAddr> BindAddr, int32 Port, bool bReuseAddressAndPort, int32 DesiredRecvSize, int32 DesiredSendSize, FString& Error) override;
	virtual FSocket* GetSocket() override;
	virtual void LowLevelSend(TSharedPtr<const FInternetAddr> Address, void* Data, int32 CountBits, FOutPacketTraits& Traits) override;
	virtual void LowLevelDestroy() override;
	virtual bool IsNetResourceValid(void) override;
	//~ End UNetDriver Interface

	virtual int32 ServerReplicateActors(float DeltaSeconds) override;
	void RegisterChannelDataProvider(IChannelDataProvider* Provider);

	UPROPERTY(Config)
	FString ChanneldIpForClient;
	UPROPERTY(Config)
	uint32 ChanneldPortForClient;
	UPROPERTY(Config)
	FString ChanneldIpForServer;
	UPROPERTY(Config)
	uint32 ChanneldPortForServer;
	UPROPERTY(Config)
	int32 ReceiveBufferSize;

	bool SendToChanneld(uint32 MessageType, const google::protobuf::Message& InMessage, uint32 ChannelId/* = 0*/);
	void ReceiveFromChanneld();

	template <typename UserClass, typename... VarTypes>
	inline void RegisterMessageHandler(uint32 MessageType, google::protobuf::Message* MessageTemplate, UserClass* InUserObject, typename TMemFunPtrType<false, UserClass, void (UChanneldClient*, uint32, const google::protobuf::Message*, VarTypes...)>::Type InFunc, VarTypes... Vars)
	{
		MessageHandlerEntry& Entry = MessageHandlers.FindOrAdd(MessageType);
		Entry.msg = MessageTemplate;
		Entry.handler.AddUObject(InUserObject, InFunc, Vars...);
	}
	inline void AddMessageHandler(uint32 MessageType, const FChanneldMessageDelegate::FDelegate& Handler)
	{
		MessageHandlerEntry& Entry = MessageHandlers.FindOrAdd(MessageType);
		Entry.handler.Add(Handler);
	}

	//TMap<ChannelId, TSubclassOf<google::protobuf::Message>> ChannelDataClasses;

	TSet<IChannelDataProvider*> ChannelDataProviders;

	channeld::TestChannelDataMessage* TestChannelData;

private:
	FUniqueSocket SocketToChanneld;
	uint8* ReceiveBuffer;
	int ReceiveBufferOffset;
	uint32 ConnId;

	struct MessageHandlerEntry
	{
		google::protobuf::Message* msg;
		FChanneldMessageDelegate handler;
	};

	TMap<uint32, MessageHandlerEntry> MessageHandlers;

	void HandleAuthResult(UChanneldClient* Client, uint32 ChannelId, const google::protobuf::Message* Msg);
	void HandleCreateChannel(UChanneldClient* Client, uint32 ChannelId, const google::protobuf::Message* Msg);
	void HandleSubToChannel(UChanneldClient* Client, uint32 ChannelId, const google::protobuf::Message* Msg);
};
