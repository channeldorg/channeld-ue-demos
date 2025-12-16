#include "CoreTypes.h"
#include "ChanneldIntegration/tps.pb.h"
#include "Containers/UnrealString.h"
#include "google/protobuf/util/json_util.h"
#include "Misc/AutomationTest.h"
#include "../DemoTypes.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FTestRepChannelDataBenchmark, "Channeld.TestRepChannelDataBenchmark", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ClientContext | EAutomationTestFlags::ServerContext | EAutomationTestFlags::PerfFilter)

const char* SrcDataJson = R"({"gameState":{"spectatorClassName":"/Script/Engine.SpectatorPawn","gameModeClassName":"/Game/Blueprints/BP_TestRepGameMode.BP_TestRepGameMode_C","bReplicatedHasBegunPlay":true},"actorStates":{"1":{"localRole":3,"remoteRole":1,"bHidden":true},"1048598":{"owningConnId":4,"bReplicateMovement":true,"localRole":3,"remoteRole":2,"owner":{"netGUID":1048590,"bunchBitsNum":0},"instigator":{"netGUID":1048598,"bunchBitsNum":0},"replicatedMovement":{"location":{"y":500,"z":118.274994}}},"1048580":{"owningConnId":3,"localRole":3,"remoteRole":1,"owner":{"netGUID":1048578,"bunchBitsNum":0},"bHidden":true},"1048586":{"owningConnId":3,"bReplicateMovement":true,"localRole":3,"remoteRole":2,"owner":{"netGUID":1048578,"bunchBitsNum":0},"instigator":{"netGUID":1048586,"bunchBitsNum":0},"replicatedMovement":{"linearVelocity":{"x":70.356514,"y":43.1561699,"z":-592.405457},"location":{"x":1180.83948,"y":767.166809,"z":118.149994},"rotation":{"y":32.5804596}}},"1048592":{"owningConnId":4,"localRole":3,"remoteRole":1,"owner":{"netGUID":1048590,"bunchBitsNum":0},"bHidden":true}},"pawnStates":{"1048598":{"playerState":{"netGUID":1048592,"bunchBitsNum":0},"controller":{"netGUID":1048590,"bunchBitsNum":0}},"1048586":{"playerState":{"netGUID":1048580,"bunchBitsNum":0},"controller":{"netGUID":1048578,"bunchBitsNum":0}}},"characterStates":{"1048586":{"basedMovement":{"movementBase":{"owner":{"netGUID":1048595,"context":[{"netGUID":1048595,"pathName":"Floor","outerGUID":3}],"netGUIDBunch":"JwGA","bunchBitsNum":0},"compName":"StaticMeshComponent0"},"bServerHasBaseComponent":true},"movementMode":1,"animRootMotionTranslationScale":1},"1048598":{"basedMovement":{"movementBase":{"owner":{"netGUID":1048595,"context":[{"netGUID":1048595,"pathName":"Floor","outerGUID":3}],"netGUIDBunch":"JwGA","bunchBitsNum":24},"compName":"StaticMeshComponent0"},"bServerHasBaseComponent":true},"movementMode":1,"animRootMotionTranslationScale":1}},"playerStates":{"1048592":{"playerId":257,"playerName":"IndieST-M16-AC36D147"},"1048580":{"playerId":256,"playerName":"IndieST-M16-C1CE32E0"}},"testGameState":{}})";
const char* DstDataJson1 = R"({"gameState":{"spectatorClassName":"/Script/Engine.SpectatorPawn","gameModeClassName":"/Game/Blueprints/BP_TestRepGameMode.BP_TestRepGameMode_C","bReplicatedHasBegunPlay":true},"actorStates":{"1048580":{"owningConnId":3,"localRole":3,"remoteRole":1,"owner":{"netGUID":1048578,"bunchBitsNum":0},"bHidden":true},"1048586":{"owningConnId":3,"bReplicateMovement":true,"localRole":3,"remoteRole":2,"owner":{"netGUID":1048578,"bunchBitsNum":0},"instigator":{"netGUID":1048586,"bunchBitsNum":0},"replicatedMovement":{"location":{"y":500,"z":118.274994}}},"1":{"localRole":3,"remoteRole":1,"bHidden":true}},"pawnStates":{"1048586":{"playerState":{"netGUID":1048580,"bunchBitsNum":0},"controller":{"netGUID":1048578,"bunchBitsNum":0}}},"characterStates":{"1048586":{"basedMovement":{"movementBase":{"owner":{"netGUID":1048595,"context":[{"netGUID":1048595,"pathName":"Floor","outerGUID":3}],"netGUIDBunch":"JwGA","bunchBitsNum":24},"compName":"StaticMeshComponent0"},"bServerHasBaseComponent":true},"movementMode":1,"animRootMotionTranslationScale":1}},"playerStates":{"1048580":{"playerId":256,"playerName":"IndieST-M16-C1CE32E0"}},"testGameState":{}})";
const char* DstDataJson2 = R"({"actorStates":{"1048598":{"replicatedMovement":{"linearVelocity":{"x":599.873718,"y":-11.7270174,"z":564.423462},"location":{"x":1484.74963,"y":897.948486,"z":139.410782},"rotation":{"y":-3.56381297}}}},"characterStates":{"1048598":{"basedMovement":{"movementBase":{"owner":{"netGUID":0}},"bServerHasBaseComponent":false},"movementMode":3}}})";

void Merge(tpspb::TestRepChannelData& Src, tpspb::TestRepChannelData& Dst)
{
	if (Src.has_gamestate())
	{
		Dst.mutable_gamestate()->MergeFrom(Src.gamestate());
	}
	if (Src.has_testgamestate())
	{
		Dst.mutable_testgamestate()->MergeFrom(Dst.testgamestate());
	}

	for (auto& Pair : Src.actorstates())
	{
		if (Pair.second.removed())
		{
			Dst.mutable_actorstates()->erase(Pair.first);
			Dst.mutable_pawnstates()->erase(Pair.first);
			Dst.mutable_characterstates()->erase(Pair.first);
			Dst.mutable_controllerstates()->erase(Pair.first);
			Dst.mutable_playercontrollerstates()->erase(Pair.first);
			Dst.mutable_testrepplayercontrollerstates()->erase(Pair.first);
		}
		else
		{
			if (Dst.actorstates().contains(Pair.first))
			{
				Dst.mutable_actorstates()->at(Pair.first).MergeFrom(Pair.second);
			}
			else
			{
				Dst.mutable_actorstates()->emplace(Pair.first, Pair.second);
			}
		}
	}

	for (auto& Pair : Src.pawnstates())
	{
		if (Dst.pawnstates().contains(Pair.first))
		{
			Dst.mutable_pawnstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst.mutable_pawnstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src.characterstates())
	{
		if (Dst.characterstates().contains(Pair.first))
		{
			Dst.mutable_characterstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst.mutable_characterstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src.playerstates())
	{
		if (Dst.playerstates().contains(Pair.first))
		{
			Dst.mutable_playerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst.mutable_playerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src.controllerstates())
	{
		if (Dst.controllerstates().contains(Pair.first))
		{
			Dst.mutable_controllerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst.mutable_controllerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src.playercontrollerstates())
	{
		if (Dst.playercontrollerstates().contains(Pair.first))
		{
			Dst.mutable_playercontrollerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst.mutable_playercontrollerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src.testrepplayercontrollerstates())
	{
		if (Dst.testrepplayercontrollerstates().contains(Pair.first))
		{
			Dst.mutable_testrepplayercontrollerstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst.mutable_testrepplayercontrollerstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src.actorcomponentstates())
	{
		if (Dst.actorcomponentstates().contains(Pair.first))
		{
			Dst.mutable_actorcomponentstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst.mutable_actorcomponentstates()->emplace(Pair.first, Pair.second);
		}
	}
	
	for (auto& Pair : Src.scenecomponentstates())
	{
		if (Dst.scenecomponentstates().contains(Pair.first))
		{
			Dst.mutable_scenecomponentstates()->at(Pair.first).MergeFrom(Pair.second);
		}
		else
		{
			Dst.mutable_scenecomponentstates()->emplace(Pair.first, Pair.second);
		}
	}
}

void DoTest(tpspb::TestRepChannelData& SrcData, tpspb::TestRepChannelData& DstData1, tpspb::TestRepChannelData& DstData2)
{
	constexpr int TIMES = 1000000;
	uint64 StartMem = FPlatformMemory::GetStats().UsedPhysical;
	uint64 StartTime = FPlatformTime::Cycles64();
	for (int i = 0; i < TIMES; i++)
	{
		Merge(DstData1, SrcData);
	}
	uint64 DurationNs = (FPlatformTime::Cycles64() - StartTime) * 1000L;
	uint64 MemInc = FPlatformMemory::GetStats().UsedPhysical - StartMem;
	UE_LOG(LogChanneldTest, Log, TEXT("Benchmark Merge1: %d ns/op, %d B inc"), DurationNs / TIMES, MemInc);

	StartMem = FPlatformMemory::GetStats().UsedPhysical;
	StartTime = FPlatformTime::Cycles64();
	for (int i = 0; i < TIMES; i++)
	{
		Merge(DstData2, SrcData);
	}
	DurationNs = (FPlatformTime::Cycles64() - StartTime) * 1000L;
	MemInc = FPlatformMemory::GetStats().UsedPhysical - StartMem;
	UE_LOG(LogChanneldTest, Log, TEXT("Benchmark Merge2: %d ns/op, %d B inc"), DurationNs / TIMES, MemInc);

	StartMem = FPlatformMemory::GetStats().UsedPhysical;
	StartTime = FPlatformTime::Cycles64();
	for (int i = 0; i < TIMES; i++)
	{
		DstData1.SerializeAsString();
	}
	DurationNs = (FPlatformTime::Cycles64() - StartTime) * 1000L;
	MemInc = FPlatformMemory::GetStats().UsedPhysical - StartMem;
	UE_LOG(LogChanneldTest, Log, TEXT("Benchmark Marshal1: %d ns/op, %d B inc"), DurationNs / TIMES, MemInc);

	StartMem = FPlatformMemory::GetStats().UsedPhysical;
	StartTime = FPlatformTime::Cycles64();
	for (int i = 0; i < TIMES; i++)
	{
		DstData2.SerializeAsString();
	}
	DurationNs = (FPlatformTime::Cycles64() - StartTime) * 1000L;
	MemInc = FPlatformMemory::GetStats().UsedPhysical - StartMem;
	UE_LOG(LogChanneldTest, Log, TEXT("Benchmark Marshal2: %d ns/op, %d B inc"), DurationNs / TIMES, MemInc);
}

bool FTestRepChannelDataBenchmark::RunTest(const FString& Parameters)
{
	tpspb::TestRepChannelData SrcData;
	google::protobuf::util::JsonStringToMessage(SrcDataJson, &SrcData);
	TestTrue(TEXT("SrcData should have ActorStates"), SrcData.actorstates_size() > 0);
	TestTrue(TEXT("SrcData should have CharacterStates"), SrcData.characterstates_size() > 0);
	TestTrue(TEXT("SrcData should have ActorStates[1048580]"), SrcData.actorstates().contains(1048580));

	tpspb::TestRepChannelData DstData1;
	google::protobuf::util::JsonStringToMessage(DstDataJson1, &DstData1);

	tpspb::TestRepChannelData DstData2;
	google::protobuf::util::JsonStringToMessage(DstDataJson1, &DstData2);

	UE_LOG(LogChanneldTest, Log, TEXT("Test with data on stack:"));
	DoTest(SrcData, DstData1, DstData2);

	google::protobuf::Arena* Arena = new google::protobuf::Arena;
	auto SrcDataHeap = Arena->CreateMessage<tpspb::TestRepChannelData>(Arena);
	google::protobuf::util::JsonStringToMessage(SrcDataJson, SrcDataHeap);

	auto DstData1Heap = Arena->CreateMessage<tpspb::TestRepChannelData>(Arena);
	google::protobuf::util::JsonStringToMessage(DstDataJson1, DstData1Heap);

	auto DstData2Heap = Arena->CreateMessage<tpspb::TestRepChannelData>(Arena);
	google::protobuf::util::JsonStringToMessage(DstDataJson2, DstData2Heap);

	UE_LOG(LogChanneldTest, Log, TEXT("Test with data on heap:"));
	DoTest(*SrcDataHeap, *DstData1Heap, *DstData2Heap);

	delete Arena;
	
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS

/*

Test with data on stack:
Benchmark Merge1: 2545 ns/op, 87461888 B inc
Benchmark Merge2: 2466 ns/op, 88883200 B inc
Benchmark Marshal1: 6393 ns/op, -417792 B inc
Benchmark Marshal2: 6430 ns/op, 0 B inc

Test with data on heap:
Benchmark Merge1: 2291 ns/op, 113135616 B inc
Benchmark Merge2: 916 ns/op, 0 B inc
Benchmark Marshal1: 6227 ns/op, 12288 B inc
Benchmark Marshal2: 3046 ns/op, 0 B inc

*/

