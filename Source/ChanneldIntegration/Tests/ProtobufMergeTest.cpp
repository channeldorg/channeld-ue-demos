// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreTypes.h"
#include "ChanneldIntegration/test.pb.h"
#include "Containers/UnrealString.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FProtobufMergeTest, "Channeld.Protobuf", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::SmokeFilter)

bool FProtobufMergeTest::RunTest(const FString& Parameters)
{
	testpb::TestMapMessage TestMsg;
	TestMsg.mutable_kv()->emplace(1, "a");
	TestMsg.mutable_kv()->emplace(2, "b");
	TestMsg.mutable_kv()->emplace(3, "c");
	TestMsg.mutable_kv()->emplace(4, "d");

	testpb::TestMapMessage_StringWrapper SW1;
	SW1.set_content("a");
	TestMsg.mutable_kv2()->emplace(1, SW1);

	testpb::TestMapMessage_StringWrapper SW2;
	SW2.set_content("b");
	SW2.set_num(2);
	TestMsg.mutable_kv2()->emplace(2, SW2);

	testpb::TestMapMessage_NullableWrapper NW1;
	NW1.set_content("c");
	NW1.set_num(3);
	TestMsg.mutable_kv3()->emplace(1, NW1);

	testpb::TestMapMessage_NullableWrapper NW2;
	NW2.set_content("d");
	NW2.set_num(4);
	TestMsg.mutable_kv3()->emplace(2, NW2);
	
	testpb::TestMapMessage UpdateMsg;
	UpdateMsg.mutable_kv()->emplace(2, "bb");
	UpdateMsg.mutable_kv()->emplace(3, "");
	UpdateMsg.mutable_kv()->emplace(4);

	UpdateMsg.mutable_kv2()->emplace(1);
	testpb::TestMapMessage_StringWrapper UpdateSW2;
	UpdateSW2.set_num(3);
	UpdateMsg.mutable_kv2()->emplace(2, UpdateSW2);

	testpb::TestMapMessage_NullableWrapper UpdateNW1;
	// Only set the num. No content.
	UpdateNW1.set_num(333);
	UpdateMsg.mutable_kv3()->emplace(1, UpdateNW1);
	
	testpb::TestMapMessage_NullableWrapper UpdateNW2;
	// Only set the content. No num.
	UpdateNW2.set_content("ddd");
	UpdateMsg.mutable_kv3()->emplace(2, UpdateNW2);
	
	TestMsg.MergeFrom(UpdateMsg);

	TestTrue(TEXT("Map's value should remain the same if the key is not updated"), TestMsg.mutable_kv()->at(1) == "a");
	TestTrue(TEXT("Map's value should be updated by key"), TestMsg.mutable_kv()->at(2) == "bb");
	TestTrue(TEXT("Map's value should be updated by key, even the new value is an empty string"), TestMsg.mutable_kv()->at(3) == "");
	// TestTrue(TEXT("Map's value should remain the same if the new value is not set"), TestMsg.mutable_kv()->at(4) == "d");
	TestTrue(TEXT("Map's value should be replaced with default value if the new value is not set"), TestMsg.mutable_kv()->at(4) == "");

	// TestTrue(TEXT("Map's obj value should remain the same if the new value is not set"), TestMsg.mutable_kv2()->at(1).content() == "a");
	TestTrue(TEXT("Map's obj value would be replaced with default if the new value is not set"), TestMsg.mutable_kv2()->at(1).content() == "");
	TestEqual(TEXT("Map's obj value should be updated"), TestMsg.mutable_kv2()->at(2).num(), (int64)3L);
	// TestTrue(TEXT("Map's obj value should remain the same if only the other key-value is updated"), TestMsg.mutable_kv2()->at(2).content() == "b");
	TestTrue(TEXT("Map's obj value would be replaced with default if only the other key-value is updated"), TestMsg.mutable_kv2()->at(2).content() == "");

	TestEqual(TEXT("Map's nullable value should be updated"), TestMsg.mutable_kv3()->at(1).num(), (int64)333L);
	// TestTrue(TEXT("Map's nullable value should remain the same if the new value is not set"), TestMsg.mutable_kv3()->at(1).content() == "c");
	TestTrue(TEXT("Map's nullable value would be replaced with default if the new value is not set"), TestMsg.mutable_kv3()->at(1).content() == "");

	TestTrue(TEXT("Map's nullable value should be updated"), TestMsg.mutable_kv3()->at(2).content() == "ddd");
	// TestEqual(TEXT("Map's nullable value should remain the same if the new value is not set"), TestMsg.mutable_kv3()->at(2).num(), 4u);
	TestEqual(TEXT("Map's nullable value would be replaced with default if the new value is not set"), TestMsg.mutable_kv3()->at(2).num(), (int64)0L);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS