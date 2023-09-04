#include "ChanneldTypes.h"
#include "CoreTypes.h"
#include "Containers/UnrealString.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStandardLayoutTest, "Channeld.StandardLayoutTest", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

struct ServerUpdateCameraParams
{
	FVector_NetQuantize CamLoc;
	int32 CamPitchAndYaw;
};

struct ClientSetHUDParams
{
	TSubclassOf<AHUD> NewHUDClass;
};

struct ClientSetViewTargetParams
{
	AActor* A;
	FViewTargetTransitionParams TransitionParams;
};

struct ClientEnableNetworkVoiceParams
{
	bool bEnable;
};

struct ClientCapBandwidthParams
{
	int32 Cap;
};

struct ClientRestartParams
{
	APawn* Pawn;
};

struct ClientSetCameraModeParams
{
	FName NewCamMode;
};

struct ClientRetryClientRestartParams
{
	APawn* Pawn;
};

struct ServerSetSpectatorLocationParams
{
	FVector NewLoc;
	FRotator NewRot;
};

struct ServerAcknowledgePossessionParams
{
	APawn* Pawn;
};

struct ClientGotoStateParams
{
	FName NewState;
};

struct ClientReceiveLocalizedMessageParams
{
	TSubclassOf<ULocalMessage> Message;
	int32 Switch;
	APlayerState* RelatedPlayerState_1;
	APlayerState* RelatedPlayerState_2;
	UObject* OptionalObject;
};

bool FStandardLayoutTest::RunTest(const FString& Parameters)
{
	TestTrue(TEXT("ServerUpdateCameraParams is standard layout"), std::is_standard_layout<ServerUpdateCameraParams>());
	TestTrue(TEXT("ClientSetHUDParams is standard layout"), std::is_standard_layout<ClientSetHUDParams>());
	TestTrue(TEXT("ClientSetViewTargetParams is standard layout"), std::is_standard_layout<ClientSetViewTargetParams>());
	TestTrue(TEXT("ClientEnableNetworkVoiceParams is standard layout"), std::is_standard_layout<ClientEnableNetworkVoiceParams>());
	TestTrue(TEXT("ClientRestartParams is standard layout"), std::is_standard_layout<ClientRestartParams>());
	TestTrue(TEXT("ClientSetCameraModeParams is standard layout"), std::is_standard_layout<ClientSetCameraModeParams>());
	TestTrue(TEXT("ServerSetSpectatorLocationParams is standard layout"), std::is_standard_layout<ServerSetSpectatorLocationParams>());
	TestTrue(TEXT("ClientReceiveLocalizedMessageParams is standard layout"), std::is_standard_layout<ClientReceiveLocalizedMessageParams>());
	TestTrue(TEXT("FChannelSubscriptionOptions is standard layout"), std::is_standard_layout<FChannelSubscriptionOptions>());
	TestTrue(TEXT("APlayerController is NOT standard layout"), !std::is_standard_layout<APlayerController>());

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS