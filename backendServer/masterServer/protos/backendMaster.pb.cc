// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: backendMaster.proto

#include "backendMaster.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

namespace backendMaster {
class EmptyRequestDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<EmptyRequest> _instance;
} _EmptyRequest_default_instance_;
class HeartbeatReplyDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<HeartbeatReply> _instance;
} _HeartbeatReply_default_instance_;
}  // namespace backendMaster
static void InitDefaultsEmptyRequest_backendMaster_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::backendMaster::_EmptyRequest_default_instance_;
    new (ptr) ::backendMaster::EmptyRequest();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::backendMaster::EmptyRequest::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_EmptyRequest_backendMaster_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsEmptyRequest_backendMaster_2eproto}, {}};

static void InitDefaultsHeartbeatReply_backendMaster_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::backendMaster::_HeartbeatReply_default_instance_;
    new (ptr) ::backendMaster::HeartbeatReply();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::backendMaster::HeartbeatReply::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_HeartbeatReply_backendMaster_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsHeartbeatReply_backendMaster_2eproto}, {}};

void InitDefaults_backendMaster_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_EmptyRequest_backendMaster_2eproto.base);
  ::google::protobuf::internal::InitSCC(&scc_info_HeartbeatReply_backendMaster_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_backendMaster_2eproto[2];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_backendMaster_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_backendMaster_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_backendMaster_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::backendMaster::EmptyRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::backendMaster::HeartbeatReply, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::backendMaster::HeartbeatReply, checkpoint_v_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::backendMaster::EmptyRequest)},
  { 5, -1, sizeof(::backendMaster::HeartbeatReply)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::backendMaster::_EmptyRequest_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::backendMaster::_HeartbeatReply_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_backendMaster_2eproto = {
  {}, AddDescriptors_backendMaster_2eproto, "backendMaster.proto", schemas,
  file_default_instances, TableStruct_backendMaster_2eproto::offsets,
  file_level_metadata_backendMaster_2eproto, 2, file_level_enum_descriptors_backendMaster_2eproto, file_level_service_descriptors_backendMaster_2eproto,
};

const char descriptor_table_protodef_backendMaster_2eproto[] =
  "\n\023backendMaster.proto\022\rbackendMaster\"\016\n\014"
  "EmptyRequest\"&\n\016HeartbeatReply\022\024\n\014checkp"
  "oint_v\030\001 \001(\0052Z\n\rBackendMaster\022I\n\theartbe"
  "at\022\033.backendMaster.EmptyRequest\032\035.backen"
  "dMaster.HeartbeatReply\"\000B2\n\025io.grpc.back"
  "endMasterB\022backendMasterProtoP\001\242\002\002BMb\006pr"
  "oto3"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_backendMaster_2eproto = {
  false, InitDefaults_backendMaster_2eproto, 
  descriptor_table_protodef_backendMaster_2eproto,
  "backendMaster.proto", &assign_descriptors_table_backendMaster_2eproto, 244,
};

void AddDescriptors_backendMaster_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_backendMaster_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_backendMaster_2eproto = []() { AddDescriptors_backendMaster_2eproto(); return true; }();
namespace backendMaster {

// ===================================================================

void EmptyRequest::InitAsDefaultInstance() {
}
class EmptyRequest::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

EmptyRequest::EmptyRequest()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:backendMaster.EmptyRequest)
}
EmptyRequest::EmptyRequest(const EmptyRequest& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:backendMaster.EmptyRequest)
}

void EmptyRequest::SharedCtor() {
}

EmptyRequest::~EmptyRequest() {
  // @@protoc_insertion_point(destructor:backendMaster.EmptyRequest)
  SharedDtor();
}

void EmptyRequest::SharedDtor() {
}

void EmptyRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const EmptyRequest& EmptyRequest::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_EmptyRequest_backendMaster_2eproto.base);
  return *internal_default_instance();
}


void EmptyRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:backendMaster.EmptyRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* EmptyRequest::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<EmptyRequest*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      default: {
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool EmptyRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:backendMaster.EmptyRequest)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
  handle_unusual:
    if (tag == 0) {
      goto success;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, _internal_metadata_.mutable_unknown_fields()));
  }
success:
  // @@protoc_insertion_point(parse_success:backendMaster.EmptyRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:backendMaster.EmptyRequest)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void EmptyRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:backendMaster.EmptyRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:backendMaster.EmptyRequest)
}

::google::protobuf::uint8* EmptyRequest::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:backendMaster.EmptyRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:backendMaster.EmptyRequest)
  return target;
}

size_t EmptyRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:backendMaster.EmptyRequest)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void EmptyRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:backendMaster.EmptyRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const EmptyRequest* source =
      ::google::protobuf::DynamicCastToGenerated<EmptyRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:backendMaster.EmptyRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:backendMaster.EmptyRequest)
    MergeFrom(*source);
  }
}

void EmptyRequest::MergeFrom(const EmptyRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:backendMaster.EmptyRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

}

void EmptyRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:backendMaster.EmptyRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void EmptyRequest::CopyFrom(const EmptyRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:backendMaster.EmptyRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool EmptyRequest::IsInitialized() const {
  return true;
}

void EmptyRequest::Swap(EmptyRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void EmptyRequest::InternalSwap(EmptyRequest* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata EmptyRequest::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_backendMaster_2eproto);
  return ::file_level_metadata_backendMaster_2eproto[kIndexInFileMessages];
}


// ===================================================================

void HeartbeatReply::InitAsDefaultInstance() {
}
class HeartbeatReply::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int HeartbeatReply::kCheckpointVFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

HeartbeatReply::HeartbeatReply()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:backendMaster.HeartbeatReply)
}
HeartbeatReply::HeartbeatReply(const HeartbeatReply& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  checkpoint_v_ = from.checkpoint_v_;
  // @@protoc_insertion_point(copy_constructor:backendMaster.HeartbeatReply)
}

void HeartbeatReply::SharedCtor() {
  checkpoint_v_ = 0;
}

HeartbeatReply::~HeartbeatReply() {
  // @@protoc_insertion_point(destructor:backendMaster.HeartbeatReply)
  SharedDtor();
}

void HeartbeatReply::SharedDtor() {
}

void HeartbeatReply::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const HeartbeatReply& HeartbeatReply::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_HeartbeatReply_backendMaster_2eproto.base);
  return *internal_default_instance();
}


void HeartbeatReply::Clear() {
// @@protoc_insertion_point(message_clear_start:backendMaster.HeartbeatReply)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  checkpoint_v_ = 0;
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* HeartbeatReply::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<HeartbeatReply*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // int32 checkpoint_v = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        msg->set_checkpoint_v(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool HeartbeatReply::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:backendMaster.HeartbeatReply)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 checkpoint_v = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &checkpoint_v_)));
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
  // @@protoc_insertion_point(parse_success:backendMaster.HeartbeatReply)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:backendMaster.HeartbeatReply)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void HeartbeatReply::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:backendMaster.HeartbeatReply)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 checkpoint_v = 1;
  if (this->checkpoint_v() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->checkpoint_v(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:backendMaster.HeartbeatReply)
}

::google::protobuf::uint8* HeartbeatReply::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:backendMaster.HeartbeatReply)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 checkpoint_v = 1;
  if (this->checkpoint_v() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->checkpoint_v(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:backendMaster.HeartbeatReply)
  return target;
}

size_t HeartbeatReply::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:backendMaster.HeartbeatReply)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 checkpoint_v = 1;
  if (this->checkpoint_v() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->checkpoint_v());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void HeartbeatReply::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:backendMaster.HeartbeatReply)
  GOOGLE_DCHECK_NE(&from, this);
  const HeartbeatReply* source =
      ::google::protobuf::DynamicCastToGenerated<HeartbeatReply>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:backendMaster.HeartbeatReply)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:backendMaster.HeartbeatReply)
    MergeFrom(*source);
  }
}

void HeartbeatReply::MergeFrom(const HeartbeatReply& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:backendMaster.HeartbeatReply)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.checkpoint_v() != 0) {
    set_checkpoint_v(from.checkpoint_v());
  }
}

void HeartbeatReply::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:backendMaster.HeartbeatReply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HeartbeatReply::CopyFrom(const HeartbeatReply& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:backendMaster.HeartbeatReply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HeartbeatReply::IsInitialized() const {
  return true;
}

void HeartbeatReply::Swap(HeartbeatReply* other) {
  if (other == this) return;
  InternalSwap(other);
}
void HeartbeatReply::InternalSwap(HeartbeatReply* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(checkpoint_v_, other->checkpoint_v_);
}

::google::protobuf::Metadata HeartbeatReply::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_backendMaster_2eproto);
  return ::file_level_metadata_backendMaster_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace backendMaster
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::backendMaster::EmptyRequest* Arena::CreateMaybeMessage< ::backendMaster::EmptyRequest >(Arena* arena) {
  return Arena::CreateInternal< ::backendMaster::EmptyRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::backendMaster::HeartbeatReply* Arena::CreateMaybeMessage< ::backendMaster::HeartbeatReply >(Arena* arena) {
  return Arena::CreateInternal< ::backendMaster::HeartbeatReply >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
