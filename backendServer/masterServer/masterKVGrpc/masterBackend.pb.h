// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: masterBackend.proto

#ifndef PROTOBUF_INCLUDED_masterBackend_2eproto
#define PROTOBUF_INCLUDED_masterBackend_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_masterBackend_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_masterBackend_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[6]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_masterBackend_2eproto();
namespace masterBackend {
class GetPrimReply;
class GetPrimReplyDefaultTypeInternal;
extern GetPrimReplyDefaultTypeInternal _GetPrimReply_default_instance_;
class GetPrimRequest;
class GetPrimRequestDefaultTypeInternal;
extern GetPrimRequestDefaultTypeInternal _GetPrimRequest_default_instance_;
class ListSubReply;
class ListSubReplyDefaultTypeInternal;
extern ListSubReplyDefaultTypeInternal _ListSubReply_default_instance_;
class ListSubRequest;
class ListSubRequestDefaultTypeInternal;
extern ListSubRequestDefaultTypeInternal _ListSubRequest_default_instance_;
class PromotePrimReply;
class PromotePrimReplyDefaultTypeInternal;
extern PromotePrimReplyDefaultTypeInternal _PromotePrimReply_default_instance_;
class PromotePrimRequest;
class PromotePrimRequestDefaultTypeInternal;
extern PromotePrimRequestDefaultTypeInternal _PromotePrimRequest_default_instance_;
}  // namespace masterBackend
namespace google {
namespace protobuf {
template<> ::masterBackend::GetPrimReply* Arena::CreateMaybeMessage<::masterBackend::GetPrimReply>(Arena*);
template<> ::masterBackend::GetPrimRequest* Arena::CreateMaybeMessage<::masterBackend::GetPrimRequest>(Arena*);
template<> ::masterBackend::ListSubReply* Arena::CreateMaybeMessage<::masterBackend::ListSubReply>(Arena*);
template<> ::masterBackend::ListSubRequest* Arena::CreateMaybeMessage<::masterBackend::ListSubRequest>(Arena*);
template<> ::masterBackend::PromotePrimReply* Arena::CreateMaybeMessage<::masterBackend::PromotePrimReply>(Arena*);
template<> ::masterBackend::PromotePrimRequest* Arena::CreateMaybeMessage<::masterBackend::PromotePrimRequest>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace masterBackend {

// ===================================================================

class GetPrimRequest final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:masterBackend.GetPrimRequest) */ {
 public:
  GetPrimRequest();
  virtual ~GetPrimRequest();

  GetPrimRequest(const GetPrimRequest& from);

  inline GetPrimRequest& operator=(const GetPrimRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetPrimRequest(GetPrimRequest&& from) noexcept
    : GetPrimRequest() {
    *this = ::std::move(from);
  }

  inline GetPrimRequest& operator=(GetPrimRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const GetPrimRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetPrimRequest* internal_default_instance() {
    return reinterpret_cast<const GetPrimRequest*>(
               &_GetPrimRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(GetPrimRequest* other);
  friend void swap(GetPrimRequest& a, GetPrimRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetPrimRequest* New() const final {
    return CreateMaybeMessage<GetPrimRequest>(nullptr);
  }

  GetPrimRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<GetPrimRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const GetPrimRequest& from);
  void MergeFrom(const GetPrimRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(GetPrimRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 my_index = 1;
  void clear_my_index();
  static const int kMyIndexFieldNumber = 1;
  ::google::protobuf::int32 my_index() const;
  void set_my_index(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:masterBackend.GetPrimRequest)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 my_index_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_masterBackend_2eproto;
};
// -------------------------------------------------------------------

class GetPrimReply final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:masterBackend.GetPrimReply) */ {
 public:
  GetPrimReply();
  virtual ~GetPrimReply();

  GetPrimReply(const GetPrimReply& from);

  inline GetPrimReply& operator=(const GetPrimReply& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  GetPrimReply(GetPrimReply&& from) noexcept
    : GetPrimReply() {
    *this = ::std::move(from);
  }

  inline GetPrimReply& operator=(GetPrimReply&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const GetPrimReply& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const GetPrimReply* internal_default_instance() {
    return reinterpret_cast<const GetPrimReply*>(
               &_GetPrimReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(GetPrimReply* other);
  friend void swap(GetPrimReply& a, GetPrimReply& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline GetPrimReply* New() const final {
    return CreateMaybeMessage<GetPrimReply>(nullptr);
  }

  GetPrimReply* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<GetPrimReply>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const GetPrimReply& from);
  void MergeFrom(const GetPrimReply& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(GetPrimReply* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 prim_index = 1;
  void clear_prim_index();
  static const int kPrimIndexFieldNumber = 1;
  ::google::protobuf::int32 prim_index() const;
  void set_prim_index(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:masterBackend.GetPrimReply)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 prim_index_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_masterBackend_2eproto;
};
// -------------------------------------------------------------------

class ListSubRequest final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:masterBackend.ListSubRequest) */ {
 public:
  ListSubRequest();
  virtual ~ListSubRequest();

  ListSubRequest(const ListSubRequest& from);

  inline ListSubRequest& operator=(const ListSubRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ListSubRequest(ListSubRequest&& from) noexcept
    : ListSubRequest() {
    *this = ::std::move(from);
  }

  inline ListSubRequest& operator=(ListSubRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const ListSubRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ListSubRequest* internal_default_instance() {
    return reinterpret_cast<const ListSubRequest*>(
               &_ListSubRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(ListSubRequest* other);
  friend void swap(ListSubRequest& a, ListSubRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ListSubRequest* New() const final {
    return CreateMaybeMessage<ListSubRequest>(nullptr);
  }

  ListSubRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ListSubRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ListSubRequest& from);
  void MergeFrom(const ListSubRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ListSubRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 my_index = 1;
  void clear_my_index();
  static const int kMyIndexFieldNumber = 1;
  ::google::protobuf::int32 my_index() const;
  void set_my_index(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:masterBackend.ListSubRequest)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 my_index_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_masterBackend_2eproto;
};
// -------------------------------------------------------------------

class ListSubReply final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:masterBackend.ListSubReply) */ {
 public:
  ListSubReply();
  virtual ~ListSubReply();

  ListSubReply(const ListSubReply& from);

  inline ListSubReply& operator=(const ListSubReply& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ListSubReply(ListSubReply&& from) noexcept
    : ListSubReply() {
    *this = ::std::move(from);
  }

  inline ListSubReply& operator=(ListSubReply&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const ListSubReply& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ListSubReply* internal_default_instance() {
    return reinterpret_cast<const ListSubReply*>(
               &_ListSubReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(ListSubReply* other);
  friend void swap(ListSubReply& a, ListSubReply& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ListSubReply* New() const final {
    return CreateMaybeMessage<ListSubReply>(nullptr);
  }

  ListSubReply* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ListSubReply>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ListSubReply& from);
  void MergeFrom(const ListSubReply& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ListSubReply* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated int32 sub_index = 1;
  int sub_index_size() const;
  void clear_sub_index();
  static const int kSubIndexFieldNumber = 1;
  ::google::protobuf::int32 sub_index(int index) const;
  void set_sub_index(int index, ::google::protobuf::int32 value);
  void add_sub_index(::google::protobuf::int32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      sub_index() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_sub_index();

  // @@protoc_insertion_point(class_scope:masterBackend.ListSubReply)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > sub_index_;
  mutable std::atomic<int> _sub_index_cached_byte_size_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_masterBackend_2eproto;
};
// -------------------------------------------------------------------

class PromotePrimRequest final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:masterBackend.PromotePrimRequest) */ {
 public:
  PromotePrimRequest();
  virtual ~PromotePrimRequest();

  PromotePrimRequest(const PromotePrimRequest& from);

  inline PromotePrimRequest& operator=(const PromotePrimRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  PromotePrimRequest(PromotePrimRequest&& from) noexcept
    : PromotePrimRequest() {
    *this = ::std::move(from);
  }

  inline PromotePrimRequest& operator=(PromotePrimRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const PromotePrimRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PromotePrimRequest* internal_default_instance() {
    return reinterpret_cast<const PromotePrimRequest*>(
               &_PromotePrimRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  void Swap(PromotePrimRequest* other);
  friend void swap(PromotePrimRequest& a, PromotePrimRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline PromotePrimRequest* New() const final {
    return CreateMaybeMessage<PromotePrimRequest>(nullptr);
  }

  PromotePrimRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<PromotePrimRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const PromotePrimRequest& from);
  void MergeFrom(const PromotePrimRequest& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PromotePrimRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 my_index = 1;
  void clear_my_index();
  static const int kMyIndexFieldNumber = 1;
  ::google::protobuf::int32 my_index() const;
  void set_my_index(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:masterBackend.PromotePrimRequest)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 my_index_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_masterBackend_2eproto;
};
// -------------------------------------------------------------------

class PromotePrimReply final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:masterBackend.PromotePrimReply) */ {
 public:
  PromotePrimReply();
  virtual ~PromotePrimReply();

  PromotePrimReply(const PromotePrimReply& from);

  inline PromotePrimReply& operator=(const PromotePrimReply& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  PromotePrimReply(PromotePrimReply&& from) noexcept
    : PromotePrimReply() {
    *this = ::std::move(from);
  }

  inline PromotePrimReply& operator=(PromotePrimReply&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const PromotePrimReply& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PromotePrimReply* internal_default_instance() {
    return reinterpret_cast<const PromotePrimReply*>(
               &_PromotePrimReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    5;

  void Swap(PromotePrimReply* other);
  friend void swap(PromotePrimReply& a, PromotePrimReply& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline PromotePrimReply* New() const final {
    return CreateMaybeMessage<PromotePrimReply>(nullptr);
  }

  PromotePrimReply* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<PromotePrimReply>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const PromotePrimReply& from);
  void MergeFrom(const PromotePrimReply& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PromotePrimReply* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string prim_index = 1;
  void clear_prim_index();
  static const int kPrimIndexFieldNumber = 1;
  const ::std::string& prim_index() const;
  void set_prim_index(const ::std::string& value);
  #if LANG_CXX11
  void set_prim_index(::std::string&& value);
  #endif
  void set_prim_index(const char* value);
  void set_prim_index(const char* value, size_t size);
  ::std::string* mutable_prim_index();
  ::std::string* release_prim_index();
  void set_allocated_prim_index(::std::string* prim_index);

  // @@protoc_insertion_point(class_scope:masterBackend.PromotePrimReply)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr prim_index_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_masterBackend_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// GetPrimRequest

// int32 my_index = 1;
inline void GetPrimRequest::clear_my_index() {
  my_index_ = 0;
}
inline ::google::protobuf::int32 GetPrimRequest::my_index() const {
  // @@protoc_insertion_point(field_get:masterBackend.GetPrimRequest.my_index)
  return my_index_;
}
inline void GetPrimRequest::set_my_index(::google::protobuf::int32 value) {
  
  my_index_ = value;
  // @@protoc_insertion_point(field_set:masterBackend.GetPrimRequest.my_index)
}

// -------------------------------------------------------------------

// GetPrimReply

// int32 prim_index = 1;
inline void GetPrimReply::clear_prim_index() {
  prim_index_ = 0;
}
inline ::google::protobuf::int32 GetPrimReply::prim_index() const {
  // @@protoc_insertion_point(field_get:masterBackend.GetPrimReply.prim_index)
  return prim_index_;
}
inline void GetPrimReply::set_prim_index(::google::protobuf::int32 value) {
  
  prim_index_ = value;
  // @@protoc_insertion_point(field_set:masterBackend.GetPrimReply.prim_index)
}

// -------------------------------------------------------------------

// ListSubRequest

// int32 my_index = 1;
inline void ListSubRequest::clear_my_index() {
  my_index_ = 0;
}
inline ::google::protobuf::int32 ListSubRequest::my_index() const {
  // @@protoc_insertion_point(field_get:masterBackend.ListSubRequest.my_index)
  return my_index_;
}
inline void ListSubRequest::set_my_index(::google::protobuf::int32 value) {
  
  my_index_ = value;
  // @@protoc_insertion_point(field_set:masterBackend.ListSubRequest.my_index)
}

// -------------------------------------------------------------------

// ListSubReply

// repeated int32 sub_index = 1;
inline int ListSubReply::sub_index_size() const {
  return sub_index_.size();
}
inline void ListSubReply::clear_sub_index() {
  sub_index_.Clear();
}
inline ::google::protobuf::int32 ListSubReply::sub_index(int index) const {
  // @@protoc_insertion_point(field_get:masterBackend.ListSubReply.sub_index)
  return sub_index_.Get(index);
}
inline void ListSubReply::set_sub_index(int index, ::google::protobuf::int32 value) {
  sub_index_.Set(index, value);
  // @@protoc_insertion_point(field_set:masterBackend.ListSubReply.sub_index)
}
inline void ListSubReply::add_sub_index(::google::protobuf::int32 value) {
  sub_index_.Add(value);
  // @@protoc_insertion_point(field_add:masterBackend.ListSubReply.sub_index)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
ListSubReply::sub_index() const {
  // @@protoc_insertion_point(field_list:masterBackend.ListSubReply.sub_index)
  return sub_index_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
ListSubReply::mutable_sub_index() {
  // @@protoc_insertion_point(field_mutable_list:masterBackend.ListSubReply.sub_index)
  return &sub_index_;
}

// -------------------------------------------------------------------

// PromotePrimRequest

// int32 my_index = 1;
inline void PromotePrimRequest::clear_my_index() {
  my_index_ = 0;
}
inline ::google::protobuf::int32 PromotePrimRequest::my_index() const {
  // @@protoc_insertion_point(field_get:masterBackend.PromotePrimRequest.my_index)
  return my_index_;
}
inline void PromotePrimRequest::set_my_index(::google::protobuf::int32 value) {
  
  my_index_ = value;
  // @@protoc_insertion_point(field_set:masterBackend.PromotePrimRequest.my_index)
}

// -------------------------------------------------------------------

// PromotePrimReply

// string prim_index = 1;
inline void PromotePrimReply::clear_prim_index() {
  prim_index_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& PromotePrimReply::prim_index() const {
  // @@protoc_insertion_point(field_get:masterBackend.PromotePrimReply.prim_index)
  return prim_index_.GetNoArena();
}
inline void PromotePrimReply::set_prim_index(const ::std::string& value) {
  
  prim_index_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:masterBackend.PromotePrimReply.prim_index)
}
#if LANG_CXX11
inline void PromotePrimReply::set_prim_index(::std::string&& value) {
  
  prim_index_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:masterBackend.PromotePrimReply.prim_index)
}
#endif
inline void PromotePrimReply::set_prim_index(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  prim_index_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:masterBackend.PromotePrimReply.prim_index)
}
inline void PromotePrimReply::set_prim_index(const char* value, size_t size) {
  
  prim_index_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:masterBackend.PromotePrimReply.prim_index)
}
inline ::std::string* PromotePrimReply::mutable_prim_index() {
  
  // @@protoc_insertion_point(field_mutable:masterBackend.PromotePrimReply.prim_index)
  return prim_index_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* PromotePrimReply::release_prim_index() {
  // @@protoc_insertion_point(field_release:masterBackend.PromotePrimReply.prim_index)
  
  return prim_index_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void PromotePrimReply::set_allocated_prim_index(::std::string* prim_index) {
  if (prim_index != nullptr) {
    
  } else {
    
  }
  prim_index_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), prim_index);
  // @@protoc_insertion_point(field_set_allocated:masterBackend.PromotePrimReply.prim_index)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace masterBackend

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_masterBackend_2eproto
