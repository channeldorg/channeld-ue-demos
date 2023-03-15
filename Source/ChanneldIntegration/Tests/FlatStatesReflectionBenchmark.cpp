#include "CoreTypes.h"
#include "FFlatStatesChannelDataProcessor.h"
#include "ChanneldIntegration/tps.pb.h"
#include "Containers/UnrealString.h"
#include "google/protobuf/util/json_util.h"
#include "Misc/AutomationTest.h"
#include "ChanneldIntegration/TpsChannelDataProcessor.h"
#include "ChanneldUETestType.h"

// #ifndef BENCHMARK
	#define BENCHMARK(TIMES, EXEC, NAME) \
	{ \
	uint64 StartMem = FPlatformMemory::GetStats().UsedPhysical; \
	uint64 StartTime = FPlatformTime::Cycles64(); \
	for (int i = 0; i < TIMES; i++) \
	{ \
	EXEC; \
	} \
	uint64 DurationNs = (FPlatformTime::Cycles64() - StartTime) * 1000L; \
	uint64 MemInc = FPlatformMemory::GetStats().UsedPhysical - StartMem; \
	UE_LOG(LogChanneldTest, Log, TEXT("Benchmark "#NAME": %d ns/op, %d B inc"), DurationNs / TIMES, MemInc); \
	} \
// #endif


#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFlatStatesReflectionBenchmark, "Channeld.FlatStatesReflectionBenchmark", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::PerfFilter)

namespace
{
	const char* FullChannelDataJson = R"({"gameState":{"spectatorClassName":"/Script/Engine.SpectatorPawn","gameModeClassName":"/Game/Blueprints/BP_TestRepGameMode.BP_TestRepGameMode_C","bReplicatedHasBegunPlay":true},"actorStates":{"1":{"localRole":3,"remoteRole":1,"bHidden":true},"1048598":{"owningConnId":4,"bReplicateMovement":true,"localRole":3,"remoteRole":2,"owner":{"netGUID":1048590,"bunchBitsNum":0},"instigator":{"netGUID":1048598,"bunchBitsNum":0},"replicatedMovement":{"location":{"y":500,"z":118.274994}}},"1048580":{"owningConnId":3,"localRole":3,"remoteRole":1,"owner":{"netGUID":1048578,"bunchBitsNum":0},"bHidden":true},"1048586":{"owningConnId":3,"bReplicateMovement":true,"localRole":3,"remoteRole":2,"owner":{"netGUID":1048578,"bunchBitsNum":0},"instigator":{"netGUID":1048586,"bunchBitsNum":0},"replicatedMovement":{"linearVelocity":{"x":70.356514,"y":43.1561699,"z":-592.405457},"location":{"x":1180.83948,"y":767.166809,"z":118.149994},"rotation":{"y":32.5804596}}},"1048592":{"owningConnId":4,"localRole":3,"remoteRole":1,"owner":{"netGUID":1048590,"bunchBitsNum":0},"bHidden":true}},"pawnStates":{"1048598":{"playerState":{"netGUID":1048592,"bunchBitsNum":0},"controller":{"netGUID":1048590,"bunchBitsNum":0}},"1048586":{"playerState":{"netGUID":1048580,"bunchBitsNum":0},"controller":{"netGUID":1048578,"bunchBitsNum":0}}},"characterStates":{"1048586":{"basedMovement":{"movementBase":{"owner":{"netGUID":1048595,"context":[{"netGUID":1048595,"pathName":"Floor","outerGUID":3}],"netGUIDBunch":"JwGA","bunchBitsNum":0},"compName":"StaticMeshComponent0"},"bServerHasBaseComponent":true},"movementMode":1,"animRootMotionTranslationScale":1},"1048598":{"basedMovement":{"movementBase":{"owner":{"netGUID":1048595,"context":[{"netGUID":1048595,"pathName":"Floor","outerGUID":3}],"netGUIDBunch":"JwGA","bunchBitsNum":24},"compName":"StaticMeshComponent0"},"bServerHasBaseComponent":true},"movementMode":1,"animRootMotionTranslationScale":1}},"playerStates":{"1048592":{"playerId":257,"playerName":"IndieST-M16-AC36D147"},"1048580":{"playerId":256,"playerName":"IndieST-M16-C1CE32E0"}},"testGameState":{}})";
	const char* SmallChannelDataJson = R"({"actorStates":{"1048598":{"replicatedMovement":{"linearVelocity":{"x":599.873718,"y":-11.7270174,"z":564.423462},"location":{"x":1484.74963,"y":897.948486,"z":139.410782},"rotation":{"y":-3.56381297}}}},"characterStates":{"1048598":{"basedMovement":{"movementBase":{"owner":{"netGUID":0}},"bServerHasBaseComponent":false},"movementMode":3}}})";
}

bool FFlatStatesReflectionBenchmark::RunTest(const FString& Parameters)
{
	google::protobuf::Arena* Arena = new google::protobuf::Arena;
	auto FullChannelData = Arena->CreateMessage<tpspb::TestRepChannelData>(Arena);
	google::protobuf::util::JsonStringToMessage(FullChannelDataJson, FullChannelData);
	TestTrue(TEXT("SrcData should have ActorStates"), FullChannelData->actorstates_size() > 0);
	TestTrue(TEXT("SrcData should have CharacterStates"), FullChannelData->characterstates_size() > 0);
	TestTrue(TEXT("SrcData should have ActorStates[1048580]"), FullChannelData->actorstates().contains(1048580));

	auto FlatProcessor = MakeUnique<FFlatStatesChannelDataProcessor>();
	bool bIsRemoved = false;
	auto ActorState = FlatProcessor->GetStateFromChannelData(FullChannelData, AActor::StaticClass(), 1048580, bIsRemoved);
	TestNotNull(TEXT("GetStateFromChannelData failed for actor state 1048580"), ActorState);
	TestFalse(TEXT("Actor state 1048580 is not removed"), bIsRemoved);

	auto TpsProcessor = MakeUnique<FTpsChannelDataProcessor>();
	
	constexpr int TIMES = 1000000;
	BENCHMARK(TIMES, TpsProcessor->GetStateFromChannelData(FullChannelData, AActor::StaticClass(), 1048580, bIsRemoved), FTpsChannelDataProcessor::GetStateFromChannelData(Full));
	BENCHMARK(TIMES, TpsProcessor->SetStateToChannelData(ActorState, FullChannelData, AActor::StaticClass(), 1048580), FTpsChannelDataProcessor::SetStateToChannelData(Full));
	BENCHMARK(TIMES, FlatProcessor->GetStateFromChannelData(FullChannelData, AActor::StaticClass(), 1048580, bIsRemoved), FFlatStatesChannelDataProcessor::GetStateFromChannelData(Full));
	BENCHMARK(TIMES, FlatProcessor->SetStateToChannelData(ActorState, FullChannelData, AActor::StaticClass(), 1048580), FFlatStatesChannelDataProcessor::SetStateToChannelData(Full));

	auto SmallChannelData = Arena->CreateMessage<tpspb::TestRepChannelData>(Arena);
	google::protobuf::util::JsonStringToMessage(SmallChannelDataJson, SmallChannelData);
	BENCHMARK(TIMES, TpsProcessor->GetStateFromChannelData(SmallChannelData, AActor::StaticClass(), 1048580, bIsRemoved), FTpsChannelDataProcessor::GetStateFromChannelData(Small));
	BENCHMARK(TIMES, TpsProcessor->SetStateToChannelData(ActorState, SmallChannelData, AActor::StaticClass(), 1048580), FTpsChannelDataProcessor::SetStateToChannelData(Small));
	BENCHMARK(TIMES, FlatProcessor->GetStateFromChannelData(SmallChannelData, AActor::StaticClass(), 1048580, bIsRemoved), FFlatStatesChannelDataProcessor::GetStateFromChannelData(Small));
	BENCHMARK(TIMES, FlatProcessor->SetStateToChannelData(ActorState, SmallChannelData, AActor::StaticClass(), 1048580), FFlatStatesChannelDataProcessor::SetStateToChannelData(Small));

	delete Arena;
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS

/*
Benchmark FTpsChannelDataProcessor::GetStateFromChannelData(Full): 113 ns/op, 0 B inc
Benchmark FTpsChannelDataProcessor::SetStateToChannelData(Full): 206 ns/op, 0 B inc
Benchmark FFlatStatesChannelDataProcessor::GetStateFromChannelData(Full): 2486 ns/op, 0 B inc
Benchmark FFlatStatesChannelDataProcessor::SetStateToChannelData(Full): 1462 ns/op, 157790208 B inc

Benchmark FTpsChannelDataProcessor::GetStateFromChannelData(Small): 91 ns/op, 0 B inc
Benchmark FTpsChannelDataProcessor::SetStateToChannelData(Small): 165 ns/op, 0 B inc
Benchmark FFlatStatesChannelDataProcessor::GetStateFromChannelData(Small): 2582 ns/op, 0 B inc
Benchmark FFlatStatesChannelDataProcessor::SetStateToChannelData(Small): 1593 ns/op, 219631616 B inc

Get: 22-28x slower
Set: 7-10x slower

*/
