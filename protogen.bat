@echo off
SET PROJECT_ROOT=%cd%
SET PROTOBUF_PATH=%PROJECT_ROOT%/Plugins/ChanneldUE/Source/ProtobufUE/ThirdParty
SET PROTOC="%PROTOBUF_PATH%/bin/protoc.exe"


cd "%PROJECT_ROOT%/Plugins/ChanneldUE/Source/ChanneldUE"

%PROTOC% --cpp_out=. --cpp_opt=dllexport_decl=CHANNELDUE_API -I "%CHANNELD_PATH%/pkg/channeldpb" -I "%PROTOBUF_PATH%/include" channeld.proto
del /q channeld.pb.cpp
rename channeld.pb.cc channeld.pb.cpp


cd "%PROJECT_ROOT%/Plugins/ChanneldUE/Source/ChanneldUE"

%PROTOC% --cpp_out=.  --cpp_opt=dllexport_decl=CHANNELDUE_API -I "%CHANNELD_PATH%/pkg/unrealpb" -I "%PROTOBUF_PATH%/include" unreal_common.proto
del /q unreal_common.pb.cpp
rename unreal_common.pb.cc unreal_common.pb.cpp


cd "%PROJECT_ROOT%/Source/ChanneldIntegration"

%PROTOC% --cpp_out=. -I "%CHANNELD_PATH%/internal/testpb" -I "%PROTOBUF_PATH%/include" test.proto
del /q test.pb.cpp
rename test.pb.cc test.pb.cpp

%PROTOC% --cpp_out=. -I "%CHANNELD_PATH%/examples/channeld-ue-chat/chatpb" chat.proto
del /q chat.pb.cpp
rename chat.pb.cc chat.pb.cpp

%PROTOC% --cpp_out=. -I "%CHANNELD_PATH%/examples/channeld-ue-tps/tpspb" -I "%CHANNELD_PATH%/pkg/unrealpb" -I "%PROTOBUF_PATH%/include" tps.proto
del /q tps.pb.cpp
rename tps.pb.cc tps.pb.cpp

pause