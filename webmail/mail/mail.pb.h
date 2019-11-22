// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: mail.proto

#ifndef PROTOBUF_INCLUDED_mail_2eproto
#define PROTOBUF_INCLUDED_mail_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_mail_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_mail_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_mail_2eproto();
namespace mail {
class Email;
class EmailDefaultTypeInternal;
extern EmailDefaultTypeInternal _Email_default_instance_;
class MailReply;
class MailReplyDefaultTypeInternal;
extern MailReplyDefaultTypeInternal _MailReply_default_instance_;
class MailRequest;
class MailRequestDefaultTypeInternal;
extern MailRequestDefaultTypeInternal _MailRequest_default_instance_;
}  // namespace mail
namespace google {
namespace protobuf {
template<> ::mail::Email* Arena::CreateMaybeMessage<::mail::Email>(Arena*);
template<> ::mail::MailReply* Arena::CreateMaybeMessage<::mail::MailReply>(Arena*);
template<> ::mail::MailRequest* Arena::CreateMaybeMessage<::mail::MailRequest>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace mail {

// ===================================================================

class MailRequest final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:mail.MailRequest) */ {
 public:
  MailRequest();
  virtual ~MailRequest();

  MailRequest(const MailRequest& from);

  inline MailRequest& operator=(const MailRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MailRequest(MailRequest&& from) noexcept
    : MailRequest() {
    *this = ::std::move(from);
  }

  inline MailRequest& operator=(MailRequest&& from) noexcept {
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
  static const MailRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MailRequest* internal_default_instance() {
    return reinterpret_cast<const MailRequest*>(
               &_MailRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(MailRequest* other);
  friend void swap(MailRequest& a, MailRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MailRequest* New() const final {
    return CreateMaybeMessage<MailRequest>(nullptr);
  }

  MailRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<MailRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const MailRequest& from);
  void MergeFrom(const MailRequest& from);
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
  void InternalSwap(MailRequest* other);
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

  // string user = 1;
  void clear_user();
  static const int kUserFieldNumber = 1;
  const ::std::string& user() const;
  void set_user(const ::std::string& value);
  #if LANG_CXX11
  void set_user(::std::string&& value);
  #endif
  void set_user(const char* value);
  void set_user(const char* value, size_t size);
  ::std::string* mutable_user();
  ::std::string* release_user();
  void set_allocated_user(::std::string* user);

  // @@protoc_insertion_point(class_scope:mail.MailRequest)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr user_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_mail_2eproto;
};
// -------------------------------------------------------------------

class MailReply final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:mail.MailReply) */ {
 public:
  MailReply();
  virtual ~MailReply();

  MailReply(const MailReply& from);

  inline MailReply& operator=(const MailReply& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  MailReply(MailReply&& from) noexcept
    : MailReply() {
    *this = ::std::move(from);
  }

  inline MailReply& operator=(MailReply&& from) noexcept {
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
  static const MailReply& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const MailReply* internal_default_instance() {
    return reinterpret_cast<const MailReply*>(
               &_MailReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(MailReply* other);
  friend void swap(MailReply& a, MailReply& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline MailReply* New() const final {
    return CreateMaybeMessage<MailReply>(nullptr);
  }

  MailReply* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<MailReply>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const MailReply& from);
  void MergeFrom(const MailReply& from);
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
  void InternalSwap(MailReply* other);
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

  // repeated .mail.Email item = 1;
  int item_size() const;
  void clear_item();
  static const int kItemFieldNumber = 1;
  ::mail::Email* mutable_item(int index);
  ::google::protobuf::RepeatedPtrField< ::mail::Email >*
      mutable_item();
  const ::mail::Email& item(int index) const;
  ::mail::Email* add_item();
  const ::google::protobuf::RepeatedPtrField< ::mail::Email >&
      item() const;

  // @@protoc_insertion_point(class_scope:mail.MailReply)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::mail::Email > item_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_mail_2eproto;
};
// -------------------------------------------------------------------

class Email final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:mail.Email) */ {
 public:
  Email();
  virtual ~Email();

  Email(const Email& from);

  inline Email& operator=(const Email& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Email(Email&& from) noexcept
    : Email() {
    *this = ::std::move(from);
  }

  inline Email& operator=(Email&& from) noexcept {
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
  static const Email& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Email* internal_default_instance() {
    return reinterpret_cast<const Email*>(
               &_Email_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Email* other);
  friend void swap(Email& a, Email& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Email* New() const final {
    return CreateMaybeMessage<Email>(nullptr);
  }

  Email* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Email>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Email& from);
  void MergeFrom(const Email& from);
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
  void InternalSwap(Email* other);
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

  // string from = 1;
  void clear_from();
  static const int kFromFieldNumber = 1;
  const ::std::string& from() const;
  void set_from(const ::std::string& value);
  #if LANG_CXX11
  void set_from(::std::string&& value);
  #endif
  void set_from(const char* value);
  void set_from(const char* value, size_t size);
  ::std::string* mutable_from();
  ::std::string* release_from();
  void set_allocated_from(::std::string* from);

  // string subject = 2;
  void clear_subject();
  static const int kSubjectFieldNumber = 2;
  const ::std::string& subject() const;
  void set_subject(const ::std::string& value);
  #if LANG_CXX11
  void set_subject(::std::string&& value);
  #endif
  void set_subject(const char* value);
  void set_subject(const char* value, size_t size);
  ::std::string* mutable_subject();
  ::std::string* release_subject();
  void set_allocated_subject(::std::string* subject);

  // string date = 3;
  void clear_date();
  static const int kDateFieldNumber = 3;
  const ::std::string& date() const;
  void set_date(const ::std::string& value);
  #if LANG_CXX11
  void set_date(::std::string&& value);
  #endif
  void set_date(const char* value);
  void set_date(const char* value, size_t size);
  ::std::string* mutable_date();
  ::std::string* release_date();
  void set_allocated_date(::std::string* date);

  // string content = 4;
  void clear_content();
  static const int kContentFieldNumber = 4;
  const ::std::string& content() const;
  void set_content(const ::std::string& value);
  #if LANG_CXX11
  void set_content(::std::string&& value);
  #endif
  void set_content(const char* value);
  void set_content(const char* value, size_t size);
  ::std::string* mutable_content();
  ::std::string* release_content();
  void set_allocated_content(::std::string* content);

  // @@protoc_insertion_point(class_scope:mail.Email)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr from_;
  ::google::protobuf::internal::ArenaStringPtr subject_;
  ::google::protobuf::internal::ArenaStringPtr date_;
  ::google::protobuf::internal::ArenaStringPtr content_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_mail_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MailRequest

// string user = 1;
inline void MailRequest::clear_user() {
  user_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& MailRequest::user() const {
  // @@protoc_insertion_point(field_get:mail.MailRequest.user)
  return user_.GetNoArena();
}
inline void MailRequest::set_user(const ::std::string& value) {
  
  user_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mail.MailRequest.user)
}
#if LANG_CXX11
inline void MailRequest::set_user(::std::string&& value) {
  
  user_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:mail.MailRequest.user)
}
#endif
inline void MailRequest::set_user(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  user_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mail.MailRequest.user)
}
inline void MailRequest::set_user(const char* value, size_t size) {
  
  user_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mail.MailRequest.user)
}
inline ::std::string* MailRequest::mutable_user() {
  
  // @@protoc_insertion_point(field_mutable:mail.MailRequest.user)
  return user_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MailRequest::release_user() {
  // @@protoc_insertion_point(field_release:mail.MailRequest.user)
  
  return user_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MailRequest::set_allocated_user(::std::string* user) {
  if (user != nullptr) {
    
  } else {
    
  }
  user_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), user);
  // @@protoc_insertion_point(field_set_allocated:mail.MailRequest.user)
}

// -------------------------------------------------------------------

// MailReply

// repeated .mail.Email item = 1;
inline int MailReply::item_size() const {
  return item_.size();
}
inline void MailReply::clear_item() {
  item_.Clear();
}
inline ::mail::Email* MailReply::mutable_item(int index) {
  // @@protoc_insertion_point(field_mutable:mail.MailReply.item)
  return item_.Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField< ::mail::Email >*
MailReply::mutable_item() {
  // @@protoc_insertion_point(field_mutable_list:mail.MailReply.item)
  return &item_;
}
inline const ::mail::Email& MailReply::item(int index) const {
  // @@protoc_insertion_point(field_get:mail.MailReply.item)
  return item_.Get(index);
}
inline ::mail::Email* MailReply::add_item() {
  // @@protoc_insertion_point(field_add:mail.MailReply.item)
  return item_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::mail::Email >&
MailReply::item() const {
  // @@protoc_insertion_point(field_list:mail.MailReply.item)
  return item_;
}

// -------------------------------------------------------------------

// Email

// string from = 1;
inline void Email::clear_from() {
  from_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Email::from() const {
  // @@protoc_insertion_point(field_get:mail.Email.from)
  return from_.GetNoArena();
}
inline void Email::set_from(const ::std::string& value) {
  
  from_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mail.Email.from)
}
#if LANG_CXX11
inline void Email::set_from(::std::string&& value) {
  
  from_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:mail.Email.from)
}
#endif
inline void Email::set_from(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  from_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mail.Email.from)
}
inline void Email::set_from(const char* value, size_t size) {
  
  from_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mail.Email.from)
}
inline ::std::string* Email::mutable_from() {
  
  // @@protoc_insertion_point(field_mutable:mail.Email.from)
  return from_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Email::release_from() {
  // @@protoc_insertion_point(field_release:mail.Email.from)
  
  return from_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Email::set_allocated_from(::std::string* from) {
  if (from != nullptr) {
    
  } else {
    
  }
  from_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from);
  // @@protoc_insertion_point(field_set_allocated:mail.Email.from)
}

// string subject = 2;
inline void Email::clear_subject() {
  subject_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Email::subject() const {
  // @@protoc_insertion_point(field_get:mail.Email.subject)
  return subject_.GetNoArena();
}
inline void Email::set_subject(const ::std::string& value) {
  
  subject_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mail.Email.subject)
}
#if LANG_CXX11
inline void Email::set_subject(::std::string&& value) {
  
  subject_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:mail.Email.subject)
}
#endif
inline void Email::set_subject(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  subject_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mail.Email.subject)
}
inline void Email::set_subject(const char* value, size_t size) {
  
  subject_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mail.Email.subject)
}
inline ::std::string* Email::mutable_subject() {
  
  // @@protoc_insertion_point(field_mutable:mail.Email.subject)
  return subject_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Email::release_subject() {
  // @@protoc_insertion_point(field_release:mail.Email.subject)
  
  return subject_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Email::set_allocated_subject(::std::string* subject) {
  if (subject != nullptr) {
    
  } else {
    
  }
  subject_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), subject);
  // @@protoc_insertion_point(field_set_allocated:mail.Email.subject)
}

// string date = 3;
inline void Email::clear_date() {
  date_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Email::date() const {
  // @@protoc_insertion_point(field_get:mail.Email.date)
  return date_.GetNoArena();
}
inline void Email::set_date(const ::std::string& value) {
  
  date_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mail.Email.date)
}
#if LANG_CXX11
inline void Email::set_date(::std::string&& value) {
  
  date_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:mail.Email.date)
}
#endif
inline void Email::set_date(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  date_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mail.Email.date)
}
inline void Email::set_date(const char* value, size_t size) {
  
  date_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mail.Email.date)
}
inline ::std::string* Email::mutable_date() {
  
  // @@protoc_insertion_point(field_mutable:mail.Email.date)
  return date_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Email::release_date() {
  // @@protoc_insertion_point(field_release:mail.Email.date)
  
  return date_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Email::set_allocated_date(::std::string* date) {
  if (date != nullptr) {
    
  } else {
    
  }
  date_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), date);
  // @@protoc_insertion_point(field_set_allocated:mail.Email.date)
}

// string content = 4;
inline void Email::clear_content() {
  content_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Email::content() const {
  // @@protoc_insertion_point(field_get:mail.Email.content)
  return content_.GetNoArena();
}
inline void Email::set_content(const ::std::string& value) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:mail.Email.content)
}
#if LANG_CXX11
inline void Email::set_content(::std::string&& value) {
  
  content_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:mail.Email.content)
}
#endif
inline void Email::set_content(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:mail.Email.content)
}
inline void Email::set_content(const char* value, size_t size) {
  
  content_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:mail.Email.content)
}
inline ::std::string* Email::mutable_content() {
  
  // @@protoc_insertion_point(field_mutable:mail.Email.content)
  return content_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Email::release_content() {
  // @@protoc_insertion_point(field_release:mail.Email.content)
  
  return content_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Email::set_allocated_content(::std::string* content) {
  if (content != nullptr) {
    
  } else {
    
  }
  content_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), content);
  // @@protoc_insertion_point(field_set_allocated:mail.Email.content)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace mail

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_mail_2eproto
