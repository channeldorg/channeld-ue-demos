// Fill out your copyright notice in the Description page of Project Settings.


#include "ChanneldNetDriver.h"

#include "Net/DataReplication.h"
#include "Net/RepLayout.h"
#include "Misc/ScopeExit.h"
#include "google/protobuf/message_lite.h"
#include "Channeld.pb.h"

DEFINE_LOG_CATEGORY(LogChanneld);

UChanneldNetDriver::UChanneldNetDriver(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ChanneldIpForServer = "127.0.0.1";
	ChanneldPortForServer = 11288;
	ChanneldIpForClient = "127.0.0.1";
	ChanneldPortForClient = 12108;
	ReceiveBufferSize = 0xffffff;
	ReceiveBuffer = new uint8[ReceiveBufferSize];

	TestChannelData = new channeld::TestChannelDataMessage();

	//TSharedRef<UChanneldNetDriver, ESPMode::ThreadSafe> SafeSP = MakeShareable(this);
	//auto Delegate = FChanneldMessageDelegate::FDelegate::CreateThreadSafeSP(SafeSP, &UChanneldNetDriver::HandleAuthResult);
	//RegisterMessageHandler((uint32)channeld::AUTH, new channeld::AuthResultMessage(), Delegate);
	RegisterMessageHandler((uint32)channeld::AUTH, new channeld::AuthResultMessage(), this, &UChanneldNetDriver::HandleAuthResult);
	RegisterMessageHandler((uint32)channeld::CREATE_CHANNEL, new channeld::CreateChannelMessage(), this, &UChanneldNetDriver::HandleCreateChannel);
	RegisterMessageHandler((uint32)channeld::SUB_TO_CHANNEL, new channeld::SubscribedToChannelResultMessage(), this, &UChanneldNetDriver::HandleSubToChannel);
	RegisterMessageHandler((uint32)channeld::CHANNEL_DATA_UPDATE, new channeld::ChannelDataUpdateMessage(), this, &UChanneldNetDriver::HandleChannelDataUpdate);
}

void UChanneldNetDriver::PostInitProperties()
{
	Super::PostInitProperties();
}

void UChanneldNetDriver::Shutdown()
{
	Super::Shutdown();

	if (SocketToChanneld.IsValid() && SocketToChanneld->GetConnectionState() == SCS_Connected)
	{
		SocketToChanneld->Close();
	}
}

bool UChanneldNetDriver::IsAvailable() const
{
	return Super::IsAvailable();
}

bool UChanneldNetDriver::InitBase(bool bInitAsClient, FNetworkNotify* InNotify, const FURL& URL,
	bool bReuseAddressAndPort, FString& Error)
{
	ISocketSubsystem* SocketSubsystem = GetSocketSubsystem();
	if (SocketSubsystem == NULL)
	{
		Error = TEXT("Unable to find socket subsystem");
		return false;
	}

	auto ChanneldAddr = SocketSubsystem->CreateInternetAddr();
	bool IsIpValid;
	if (bInitAsClient)
	{
		ChanneldAddr->SetIp(*ChanneldIpForClient, IsIpValid);
		if (!IsIpValid)
		{
			Error = FString::Printf(TEXT("Invalid IP for client: %s"), *ChanneldIpForClient);
			return false;
		}
		ChanneldAddr->SetPort(ChanneldPortForClient);
	}
	else
	{
		ChanneldAddr->SetIp(*ChanneldIpForServer, IsIpValid);
		if (!IsIpValid)
		{
			Error = FString::Printf(TEXT("Invalid IP for server: %s"), *ChanneldIpForServer);
			return false;
		}
		ChanneldAddr->SetPort(ChanneldPortForServer);
	}

	// Create TCP socket to channeld
	SocketToChanneld = SocketSubsystem->CreateUniqueSocket(NAME_Stream, TEXT("Connection to channeld"), ChanneldAddr->GetProtocolType());
	UE_LOG(LogChanneld, Log, TEXT("Connecting to channeld with addr: %s"), *ChanneldAddr->ToString(true));
	
	if (SocketToChanneld->Connect(*ChanneldAddr))
	{

		channeld::AuthMessage AuthMsg;
		AuthMsg.set_playeridentifiertoken("test_pit");
		AuthMsg.set_logintoken("test_lt");
		SendToChanneld(channeld::AUTH, AuthMsg, 0);
	}
	else
	{
		Error = TEXT("Failed to connect to channeld");
		return false;
	}

	return Super::InitBase(bInitAsClient, InNotify, URL, bReuseAddressAndPort, Error);
}

bool UChanneldNetDriver::InitConnect(FNetworkNotify* InNotify, const FURL& ConnectURL, FString& Error)
{
	return Super::InitConnect(InNotify, ConnectURL, Error);
}

bool UChanneldNetDriver::InitListen(FNetworkNotify* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error)
{
	return Super::InitListen(InNotify, LocalURL, bReuseAddressAndPort, Error);
}

ISocketSubsystem* UChanneldNetDriver::GetSocketSubsystem()
{
	return Super::GetSocketSubsystem();
}


FUniqueSocket UChanneldNetDriver::CreateSocketForProtocol(const FName& ProtocolType)
{
	ISocketSubsystem* SocketSubsystem = GetSocketSubsystem();

	if (SocketSubsystem == NULL)
	{
		UE_LOG(LogNet, Warning, TEXT("UChanneldNetDriver::CreateSocket: Unable to find socket subsystem"));
		return NULL;
	}

	return SocketSubsystem->CreateUniqueSocket(NAME_DGram, TEXT("Connection to channeld"), ProtocolType);
}

FUniqueSocket UChanneldNetDriver::CreateAndBindSocket(TSharedRef<FInternetAddr> BindAddr, int32 Port, bool bReuseAddressAndPort, int32 DesiredRecvSize, int32 DesiredSendSize, FString& Error)
{
	ISocketSubsystem* SocketSubsystem = GetSocketSubsystem();
	if (SocketSubsystem == nullptr)
	{
		Error = TEXT("Unable to find socket subsystem");
		return nullptr;
	}

	// Create the socket that we will use to communicate with
	FUniqueSocket NewSocket = CreateSocketForProtocol(BindAddr->GetProtocolType());

	if (!NewSocket.IsValid())
	{
		Error = FString::Printf(TEXT("%s: socket failed (%i)"), SocketSubsystem->GetSocketAPIName(), (int32)SocketSubsystem->GetLastErrorCode());
		return nullptr;
	}

	/* Make sure to cleanly destroy any sockets we do not mean to use. */
	ON_SCOPE_EXIT
	{
		if (Error.IsEmpty() == false)
		{
			NewSocket.Reset();
		}
	};

	//if (SocketSubsystem->RequiresChatDataBeSeparate() == false && NewSocket->SetBroadcast() == false)
	//{
	//	Error = FString::Printf(TEXT("%s: setsockopt SO_BROADCAST failed (%i)"), SocketSubsystem->GetSocketAPIName(), (int32)SocketSubsystem->GetLastErrorCode());
	//	return nullptr;
	//}

	if (NewSocket->SetReuseAddr(bReuseAddressAndPort) == false)
	{
		UE_LOG(LogNet, Log, TEXT("setsockopt with SO_REUSEADDR failed"));
	}

	if (NewSocket->SetRecvErr() == false)
	{
		UE_LOG(LogNet, Log, TEXT("setsockopt with IP_RECVERR failed"));
	}

	int32 ActualRecvSize(0);
	int32 ActualSendSize(0);
	NewSocket->SetReceiveBufferSize(DesiredRecvSize, ActualRecvSize);
	NewSocket->SetSendBufferSize(DesiredSendSize, ActualSendSize);
	UE_LOG(LogInit, Log, TEXT("%s: Socket queue. Rx: %i (config %i) Tx: %i (config %i)"), SocketSubsystem->GetSocketAPIName(),
		ActualRecvSize, DesiredRecvSize, ActualSendSize, DesiredSendSize);

	// Bind socket to our port.
	BindAddr->SetPort(Port);

	int32 AttemptPort = BindAddr->GetPort();
	int32 BoundPort = SocketSubsystem->BindNextPort(NewSocket.Get(), *BindAddr, MaxPortCountToTry + 1, 1);
	if (BoundPort == 0)
	{
		Error = FString::Printf(TEXT("%s: binding to port %i failed (%i)"), SocketSubsystem->GetSocketAPIName(), AttemptPort,
			(int32)SocketSubsystem->GetLastErrorCode());
		return nullptr;
	}
	if (NewSocket->SetNonBlocking() == false)
	{
		Error = FString::Printf(TEXT("%s: SetNonBlocking failed (%i)"), SocketSubsystem->GetSocketAPIName(),
			(int32)SocketSubsystem->GetLastErrorCode());
		return nullptr;
	}

	return NewSocket;
}

FSocket* UChanneldNetDriver::GetSocket()
{
	return Super::GetSocket();
	// TODO: return the Socket to channeld

	// SetSocket can't be overriden
}

void UChanneldNetDriver::LowLevelSend(TSharedPtr<const FInternetAddr> Address, void* Data, int32 CountBits,
	FOutPacketTraits& Traits)
{
	return Super::LowLevelSend(Address, Data, CountBits, Traits);
}

void UChanneldNetDriver::LowLevelDestroy()
{
	return Super::LowLevelDestroy();
}

bool UChanneldNetDriver::IsNetResourceValid()
{
	return Super::IsNetResourceValid();
}

void UChanneldNetDriver::RegisterChannelDataProvider(IChannelDataProvider* Provider)
{
	ChannelDataProviders.Add(Provider);
}

int32 UChanneldNetDriver::ServerReplicateActors(float DeltaSeconds)
{
	auto const Result = Super::ServerReplicateActors(DeltaSeconds);

	int32 Updated = 0;
	for (auto const Provider : ChannelDataProviders)
	{
		Updated += Provider->UpdateChannelData(TestChannelData);
	}

	if (Updated > 0)
	{
		const auto ByteString = TestChannelData->SerializeAsString();
		UE_LOG(LogTemp, Log, TEXT("TestChannelData has %d update(s). Serialized: %s"), Updated, ByteString.c_str());

		// Send to channeld
		channeld::ChannelDataUpdateMessage UpdateMsg;
		UpdateMsg.mutable_data()->PackFrom(*TestChannelData);
		SendToChanneld(channeld::CHANNEL_DATA_UPDATE, UpdateMsg, 0);
	}

	return Result;
}

/* Transport Level Code */
bool UChanneldNetDriver::SendToChanneld(channeld::MessageType MsgType, google::protobuf::Message& InMessage, ChannelId ChannelId = 0)
{
	uint8* MessageData = new uint8[InMessage.ByteSizeLong()];
	bool Serialized = InMessage.SerializeToArray(MessageData, InMessage.GetCachedSize());
	if (!Serialized)
	{
		delete[] MessageData;
		UE_LOG(LogChanneld, Log, TEXT("Failed to serialize InMessage, message type: %d"), MsgType);
		return false;
	}

	channeld::Packet InPacket;
	channeld::MessagePack* InMessagePack = InPacket.add_messages();
	InMessagePack->set_channelid(ChannelId);
	InMessagePack->set_broadcast(channeld::NO_BROADCAST);
	InMessagePack->set_stubid(0);
	InMessagePack->set_msgtype((uint32)MsgType);
	InMessagePack->set_msgbody(MessageData, InMessage.GetCachedSize());

	int PacketSize = InPacket.ByteSizeLong();
	int TotalSize = PacketSize + 5;
	uint8* PacketData = new uint8[TotalSize];
	Serialized = InPacket.SerializeToArray(PacketData + 5, PacketSize);
	if (!Serialized)
	{
		delete[] MessageData;
		delete[] PacketData;
		UE_LOG(LogChanneld, Log, TEXT("Failed to serialize Packet, message type: %d"), MsgType);
		return false;
	}

	PacketData[0] = 67;
	PacketData[1] = PacketSize > 0xffff ? (uint8)((PacketSize >> 16) & 0xff) : 72;
	PacketData[2] = PacketSize > 0xff ? (uint8)((PacketSize >> 8) & 0xff) : 78;
	PacketData[3] = (uint8)(PacketSize & 0xff);
	// TODO: support Snappy compression
	PacketData[4] = 0;

	int32 BytesSent;
	bool IsSent = SocketToChanneld->Send(PacketData, TotalSize, BytesSent);
	// Free send buffer
	delete[] MessageData;
	delete[] PacketData;

	if (IsSent)
	{
		// Also free up the memory used by the protobuf object
		InMessage.Clear();

		UE_LOG(LogChanneld, Log, TEXT("Sent packet to channeld, message type: %d, size: %d/%d"), MsgType, BytesSent, TotalSize);
		return BytesSent == sizeof(PacketData);
	}
	else
	{
		UE_LOG(LogChanneld, Log, TEXT("Failed to send packet to channeld, message type: %d"), MsgType);
		return false;
	}
}
/* End of Transport Level Code */

void UChanneldNetDriver::TickDispatch(float DeltaTime)
{
	Super::TickDispatch(DeltaTime);

/*

	for (const auto ObjRep : AllOwnedReplicators)
	{
		ObjRep->RepState->GetSendingRepState()->RepChangedPropertyTracker->Parents;
	}

	for (const auto& Pair : ReplicationChangeListMap)
	{
		const auto RepLayout = GetObjectClassRepLayout(Pair.Key->GetClass());
		const auto State = Pair.Value->GetRepChangelistState();
		const auto History = State->ChangeHistory[State->HistoryEnd];
		for (const auto CmdIndex : History.Changed)
		{
			const auto Property = RepLayout->Cmds[CmdIndex].Property;
			
		}

		const auto Properties = Pair.Value->GetRepChangelistState()->SharedSerialization.SharedPropertyInfo;
		for (const auto& Property : Properties)
		{
			Property.PropertyKey.ToDebugString();
		}
	}
*/
	if (SocketToChanneld->GetConnectionState() == SCS_Connected)
	{
		ReceiveFromChanneld();
	}
}

/* Transport Level Code */

void UChanneldNetDriver::ReceiveFromChanneld()
{
	int32 BytesRead;
	if (SocketToChanneld->Recv(ReceiveBuffer + ReceiveBufferOffset, ReceiveBufferSize, BytesRead, ESocketReceiveFlags::None))
	{
		ReceiveBufferOffset += BytesRead;
		if (BytesRead < 5)
		{
			// Unfinished packet
			return;
		}

		if (ReceiveBuffer[0] != 67)
		{
			ReceiveBufferOffset = 0;
			UE_LOG(LogChanneld, Error, TEXT("Invalid tag: %d, the packet will be dropped"), ReceiveBuffer[0]);
			return;
		}

		int32 PacketSize = ReceiveBuffer[3];
		if (ReceiveBuffer[1] != 72)
			PacketSize = PacketSize | (ReceiveBuffer[1]<<16) | (ReceiveBuffer[2]<<8);
		else if (ReceiveBuffer[2] != 78)
			PacketSize = PacketSize | (ReceiveBuffer[2]<<8);

		if (BytesRead < 5 + PacketSize)
		{
			// Unfinished packet
			return;
		}

		// TODO: support Snappy compression

		channeld::Packet Packet;
		if (!Packet.ParseFromArray(ReceiveBuffer + 5, PacketSize))
		{
			ReceiveBufferOffset = 0;
			UE_LOG(LogChanneld, Error, TEXT("Failed to parse packet"));
			return;
		}

		for (auto const MessagePack : Packet.messages())
		{
			uint32 MsgType = MessagePack.msgtype();

			if (!MessageHandlers.Contains(MsgType))
			{
				UE_LOG(LogChanneld, Warning, TEXT("No message handler registered for type: %d"), MessagePack.msgtype());
				continue;
			}
			auto Entry = MessageHandlers[MsgType];
			if (Entry.msg == nullptr)
			{
				UE_LOG(LogChanneld, Error, TEXT("No message template registered for type: %d"), MessagePack.msgtype());
				continue;
			}

			// Always make a clone!
			google::protobuf::Message* msg = Entry.msg->New();
			msg->CopyFrom(*Entry.msg);
			if (!msg->ParseFromString(MessagePack.msgbody()))
			{
				UE_LOG(LogChanneld, Error, TEXT("Failed to parse message %s"), msg->GetTypeName().c_str());
				continue;
			}

			Entry.handler.Broadcast(nullptr, MessagePack.channelid(), msg);
		}

	}
	else
	{
		// Handle disconnection or exception
		UE_LOG(LogChanneld, Warning, TEXT("Failed to receive data from channeld"));		
	}

	// Reset read position
	ReceiveBufferOffset = 0;
}
/* End of Transport Level Code */

void UChanneldNetDriver::HandleAuthResult(UChanneldClient* Client, ChannelId ChannelId, const google::protobuf::Message* Msg)
{
	auto AuthResultMsg = static_cast<const channeld::AuthResultMessage*>(Msg);
	if (AuthResultMsg->result() == channeld::AuthResultMessage_AuthResult_SUCCESSFUL)
	{
		ConnId = AuthResultMsg->connid();
		UE_LOG(LogChanneld, Log, TEXT("[%s] Successed to get authorization by channeld, connId: %d"), *GetWorld()->GetDebugDisplayName(), ConnId);
	}
	else
	{
		UE_LOG(LogChanneld, Error, TEXT("[%s] Failed to get authorization by channeld"), *GetWorld()->GetDebugDisplayName());
		return;
	}

	if (IsServer())
	{
		channeld::CreateChannelMessage CreateMsg;
		CreateMsg.set_channeltype(channeld::GLOBAL);
		CreateMsg.set_metadata("test123");
		CreateMsg.mutable_data()->PackFrom(*TestChannelData);
		SendToChanneld(channeld::CREATE_CHANNEL, CreateMsg, 0);
	}
	else
	{
		channeld::SubscribedToChannelMessage SubMsg;
		SubMsg.set_connid(ConnId);
		SendToChanneld(channeld::SUB_TO_CHANNEL, SubMsg, 0);
	}
}


void UChanneldNetDriver::HandleCreateChannel(UChanneldClient* Client, ChannelId ChId, const google::protobuf::Message* Msg)
{
	auto CreateResultMsg = static_cast<const channeld::CreateChannelResultMessage*>(Msg);
	UE_LOG(LogChanneld, Log, TEXT("[%s] Created channel: %d, type: %s, owner connId: %d"), *GetWorld()->GetDebugDisplayName(),
		ChId, channeld::ChannelType_Name(CreateResultMsg->channeltype()).c_str(), CreateResultMsg->ownerconnid());

	for (auto const Provider : ChannelDataProviders)
	{
		if (Provider->GetChannelType() == CreateResultMsg->channeltype())
		{
			Provider->SetChannelId(ChId);
		}
	}
}

void UChanneldNetDriver::HandleSubToChannel(UChanneldClient* Client, ChannelId ChId, const google::protobuf::Message* Msg)
{
	auto SubResultMsg = static_cast<const channeld::SubscribedToChannelResultMessage*>(Msg);
	UE_LOG(LogChanneld, Log, TEXT("[%s] Sub to channel: %d, connId: %d"), *GetWorld()->GetDebugDisplayName(), ChId, SubResultMsg->connid());
}

void UChanneldNetDriver::HandleChannelDataUpdate(UChanneldClient* Client, ChannelId ChId, const google::protobuf::Message* Msg)
{
	auto UpdateMsg = static_cast<const channeld::ChannelDataUpdateMessage*>(Msg);
	for (auto const Provider : ChannelDataProviders)
	{
		if (Provider->GetChannelId() == ChId)
		{
			Provider->OnChannelDataUpdated(UpdateMsg);
		}
	}
}


