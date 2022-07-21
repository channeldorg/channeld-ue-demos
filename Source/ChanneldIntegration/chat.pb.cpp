// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: chat.proto

// Disable UE4 VS warnings
#ifdef _MSC_VER
#	pragma warning(disable: 4946)
#	pragma warning(disable: 4125)
#	pragma warning(disable: 4647)
#	pragma warning(disable: 4668)
#	pragma warning(disable: 4800)
#endif

#include "chat.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)
namespace chatpb {
class ChatMessageDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<ChatMessage>
      _instance;
} _ChatMessage_default_instance_;
class ChatChannelDataDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<ChatChannelData>
      _instance;
} _ChatChannelData_default_instance_;
}  // namespace chatpb
namespace protobuf_chat_2eproto {
void InitDefaultsChatMessageImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::chatpb::_ChatMessage_default_instance_;
    new (ptr) ::chatpb::ChatMessage();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::chatpb::ChatMessage::InitAsDefaultInstance();
}

void InitDefaultsChatMessage() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsChatMessageImpl);
}

void InitDefaultsChatChannelDataImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  protobuf_chat_2eproto::InitDefaultsChatMessage();
  {
    void* ptr = &::chatpb::_ChatChannelData_default_instance_;
    new (ptr) ::chatpb::ChatChannelData();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::chatpb::ChatChannelData::InitAsDefaultInstance();
}

void InitDefaultsChatChannelData() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsChatChannelDataImpl);
}

::google::protobuf::Metadata file_level_metadata[2];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chatpb::ChatMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chatpb::ChatMessage, sender_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chatpb::ChatMessage, sendtime_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chatpb::ChatMessage, content_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chatpb::ChatMessage, senderconnid_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chatpb::ChatMessage, chatchanneltype_),
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chatpb::ChatChannelData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chatpb::ChatChannelData, chatmessages_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::chatpb::ChatMessage)},
  { 10, -1, sizeof(::chatpb::ChatChannelData)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::chatpb::_ChatMessage_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::chatpb::_ChatChannelData_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "chat.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, file_level_enum_descriptors, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\nchat.proto\022\006chatpb\"\210\001\n\013ChatMessage\022\016\n\006"
      "sender\030\001 \001(\t\022\020\n\010sendTime\030\002 \001(\003\022\017\n\007conten"
      "t\030\003 \001(\t\022\024\n\014senderConnId\030\004 \001(\r\0220\n\017chatCha"
      "nnelType\030\005 \001(\0162\027.chatpb.ChatChannelType\""
      "<\n\017ChatChannelData\022)\n\014chatMessages\030\001 \003(\013"
      "2\023.chatpb.ChatMessage*E\n\017ChatChannelType"
      "\022\013\n\007UNKNOWN\020\000\022\n\n\006GLOBAL\020\001\022\013\n\007PRIVATE\020\002\022\014"
      "\n\010SUBWORLD\020\003b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 300);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "chat.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_chat_2eproto
namespace chatpb {
const ::google::protobuf::EnumDescriptor* ChatChannelType_descriptor() {
  protobuf_chat_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_chat_2eproto::file_level_enum_descriptors[0];
}
bool ChatChannelType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}


// ===================================================================

void ChatMessage::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ChatMessage::kSenderFieldNumber;
const int ChatMessage::kSendTimeFieldNumber;
const int ChatMessage::kContentFieldNumber;
const int ChatMessage::kSenderConnIdFieldNumber;
const int ChatMessage::kChatChannelTypeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ChatMessage::ChatMessage()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_chat_2eproto::InitDefaultsChatMessage();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:chatpb.ChatMessage)
}
ChatMessage::ChatMessage(const ChatMessage& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  sender_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.sender().size() > 0) {
    sender_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.sender_);
  }
  content_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.content().size() > 0) {
    content_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.content_);
  }
  ::memcpy(&sendtime_, &from.sendtime_,
    static_cast<size_t>(reinterpret_cast<char*>(&chatchanneltype_) -
    reinterpret_cast<char*>(&sendtime_)) + sizeof(chatchanneltype_));
  // @@protoc_insertion_point(copy_constructor:chatpb.ChatMessage)
}

void ChatMessage::SharedCtor() {
  sender_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  content_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&sendtime_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&chatchanneltype_) -
      reinterpret_cast<char*>(&sendtime_)) + sizeof(chatchanneltype_));
  _cached_size_ = 0;
}

ChatMessage::~ChatMessage() {
  // @@protoc_insertion_point(destructor:chatpb.ChatMessage)
  SharedDtor();
}

void ChatMessage::SharedDtor() {
  sender_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  content_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void ChatMessage::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ChatMessage::descriptor() {
  ::protobuf_chat_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_chat_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const ChatMessage& ChatMessage::default_instance() {
  ::protobuf_chat_2eproto::InitDefaultsChatMessage();
  return *internal_default_instance();
}

ChatMessage* ChatMessage::New(::google::protobuf::Arena* arena) const {
  ChatMessage* n = new ChatMessage;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ChatMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:chatpb.ChatMessage)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  sender_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  content_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&sendtime_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&chatchanneltype_) -
      reinterpret_cast<char*>(&sendtime_)) + sizeof(chatchanneltype_));
  _internal_metadata_.Clear();
}

bool ChatMessage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:chatpb.ChatMessage)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string sender = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_sender()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->sender().data(), static_cast<int>(this->sender().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "chatpb.ChatMessage.sender"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int64 sendTime = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &sendtime_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string content = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_content()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->content().data(), static_cast<int>(this->content().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "chatpb.ChatMessage.content"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // uint32 senderConnId = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &senderconnid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .chatpb.ChatChannelType chatChannelType = 5;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(40u /* 40 & 0xFF */)) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_chatchanneltype(static_cast< ::chatpb::ChatChannelType >(value));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:chatpb.ChatMessage)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:chatpb.ChatMessage)
  return false;
#undef DO_
}

void ChatMessage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:chatpb.ChatMessage)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string sender = 1;
  if (this->sender().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->sender().data(), static_cast<int>(this->sender().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "chatpb.ChatMessage.sender");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->sender(), output);
  }

  // int64 sendTime = 2;
  if (this->sendtime() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->sendtime(), output);
  }

  // string content = 3;
  if (this->content().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->content().data(), static_cast<int>(this->content().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "chatpb.ChatMessage.content");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->content(), output);
  }

  // uint32 senderConnId = 4;
  if (this->senderconnid() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->senderconnid(), output);
  }

  // .chatpb.ChatChannelType chatChannelType = 5;
  if (this->chatchanneltype() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      5, this->chatchanneltype(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:chatpb.ChatMessage)
}

::google::protobuf::uint8* ChatMessage::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:chatpb.ChatMessage)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string sender = 1;
  if (this->sender().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->sender().data(), static_cast<int>(this->sender().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "chatpb.ChatMessage.sender");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->sender(), target);
  }

  // int64 sendTime = 2;
  if (this->sendtime() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(2, this->sendtime(), target);
  }

  // string content = 3;
  if (this->content().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->content().data(), static_cast<int>(this->content().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "chatpb.ChatMessage.content");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->content(), target);
  }

  // uint32 senderConnId = 4;
  if (this->senderconnid() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->senderconnid(), target);
  }

  // .chatpb.ChatChannelType chatChannelType = 5;
  if (this->chatchanneltype() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      5, this->chatchanneltype(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:chatpb.ChatMessage)
  return target;
}

size_t ChatMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:chatpb.ChatMessage)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string sender = 1;
  if (this->sender().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->sender());
  }

  // string content = 3;
  if (this->content().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->content());
  }

  // int64 sendTime = 2;
  if (this->sendtime() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->sendtime());
  }

  // uint32 senderConnId = 4;
  if (this->senderconnid() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->senderconnid());
  }

  // .chatpb.ChatChannelType chatChannelType = 5;
  if (this->chatchanneltype() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->chatchanneltype());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ChatMessage::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:chatpb.ChatMessage)
  GOOGLE_DCHECK_NE(&from, this);
  const ChatMessage* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const ChatMessage>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:chatpb.ChatMessage)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:chatpb.ChatMessage)
    MergeFrom(*source);
  }
}

void ChatMessage::MergeFrom(const ChatMessage& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:chatpb.ChatMessage)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.sender().size() > 0) {

    sender_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.sender_);
  }
  if (from.content().size() > 0) {

    content_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.content_);
  }
  if (from.sendtime() != 0) {
    set_sendtime(from.sendtime());
  }
  if (from.senderconnid() != 0) {
    set_senderconnid(from.senderconnid());
  }
  if (from.chatchanneltype() != 0) {
    set_chatchanneltype(from.chatchanneltype());
  }
}

void ChatMessage::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:chatpb.ChatMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ChatMessage::CopyFrom(const ChatMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:chatpb.ChatMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChatMessage::IsInitialized() const {
  return true;
}

void ChatMessage::Swap(ChatMessage* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ChatMessage::InternalSwap(ChatMessage* other) {
  using std::swap;
  sender_.Swap(&other->sender_);
  content_.Swap(&other->content_);
  swap(sendtime_, other->sendtime_);
  swap(senderconnid_, other->senderconnid_);
  swap(chatchanneltype_, other->chatchanneltype_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ChatMessage::GetMetadata() const {
  protobuf_chat_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_chat_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void ChatChannelData::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int ChatChannelData::kChatMessagesFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

ChatChannelData::ChatChannelData()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_chat_2eproto::InitDefaultsChatChannelData();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:chatpb.ChatChannelData)
}
ChatChannelData::ChatChannelData(const ChatChannelData& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      chatmessages_(from.chatmessages_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:chatpb.ChatChannelData)
}

void ChatChannelData::SharedCtor() {
  _cached_size_ = 0;
}

ChatChannelData::~ChatChannelData() {
  // @@protoc_insertion_point(destructor:chatpb.ChatChannelData)
  SharedDtor();
}

void ChatChannelData::SharedDtor() {
}

void ChatChannelData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ChatChannelData::descriptor() {
  ::protobuf_chat_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_chat_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const ChatChannelData& ChatChannelData::default_instance() {
  ::protobuf_chat_2eproto::InitDefaultsChatChannelData();
  return *internal_default_instance();
}

ChatChannelData* ChatChannelData::New(::google::protobuf::Arena* arena) const {
  ChatChannelData* n = new ChatChannelData;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void ChatChannelData::Clear() {
// @@protoc_insertion_point(message_clear_start:chatpb.ChatChannelData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  chatmessages_.Clear();
  _internal_metadata_.Clear();
}

bool ChatChannelData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:chatpb.ChatChannelData)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .chatpb.ChatMessage chatMessages = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(input, add_chatmessages()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:chatpb.ChatChannelData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:chatpb.ChatChannelData)
  return false;
#undef DO_
}

void ChatChannelData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:chatpb.ChatChannelData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .chatpb.ChatMessage chatMessages = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->chatmessages_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->chatmessages(static_cast<int>(i)), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:chatpb.ChatChannelData)
}

::google::protobuf::uint8* ChatChannelData::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:chatpb.ChatChannelData)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .chatpb.ChatMessage chatMessages = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->chatmessages_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageToArray(
        1, this->chatmessages(static_cast<int>(i)), deterministic, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:chatpb.ChatChannelData)
  return target;
}

size_t ChatChannelData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:chatpb.ChatChannelData)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated .chatpb.ChatMessage chatMessages = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->chatmessages_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSize(
          this->chatmessages(static_cast<int>(i)));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ChatChannelData::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:chatpb.ChatChannelData)
  GOOGLE_DCHECK_NE(&from, this);
  const ChatChannelData* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const ChatChannelData>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:chatpb.ChatChannelData)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:chatpb.ChatChannelData)
    MergeFrom(*source);
  }
}

void ChatChannelData::MergeFrom(const ChatChannelData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:chatpb.ChatChannelData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  chatmessages_.MergeFrom(from.chatmessages_);
}

void ChatChannelData::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:chatpb.ChatChannelData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ChatChannelData::CopyFrom(const ChatChannelData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:chatpb.ChatChannelData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ChatChannelData::IsInitialized() const {
  return true;
}

void ChatChannelData::Swap(ChatChannelData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void ChatChannelData::InternalSwap(ChatChannelData* other) {
  using std::swap;
  chatmessages_.InternalSwap(&other->chatmessages_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata ChatChannelData::GetMetadata() const {
  protobuf_chat_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_chat_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace chatpb

// @@protoc_insertion_point(global_scope)