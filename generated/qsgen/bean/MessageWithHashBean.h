// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#ifndef MESSAGEWITHHASHBEAN_H
#define MESSAGEWITHHASHBEAN_H

#include <CppBeans.h>

#include <folly/io/IOBuf.h>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class MessageWithHashBean {
public:
  MessageWithHashBean() = default;

  MessageWithHashBean(const char *json)
      : MessageWithHashBean(rapidjson::Document{}.Parse(json)) {}

  MessageWithHashBean(std::string hash, std::string message)
      : hash(hash), message(message) {}

  MessageWithHashBean(const rapidjson::Value &value) {
    if (value.HasMember(hash_label))
      this->hash = Typoid<std::string>::FromValue(value[hash_label]);
    else
      throw(missing_mandatory_field(hash_label));
    if (value.HasMember(message_label))
      this->message = Typoid<std::string>::FromValue(value[message_label]);
    else
      throw(missing_mandatory_field(message_label));
  }

  void update(MessageWithHashBean bean) {
    hash = bean.hash;
    message = bean.message;
  }

  template <typename Writer> void Serialize(Writer &writer) const {
    writer.StartObject();
    writer.String(hash_label);
    Typoid<std::string>::Serialize(hash, writer);
    writer.String(message_label);
    Typoid<std::string>::Serialize(message, writer);
    writer.EndObject();
  }

  std::string to_string() const {
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    Serialize(writer);
    return s.GetString();
  }

  operator std::unique_ptr<folly::IOBuf>() const {
    return folly::IOBuf::copyBuffer(::serialize(*this));
  }

  const char *__name__ = "MessageWithHashBean";
  std::string hash;
  const char *hash_label = "hash";
  std::string message;
  const char *message_label = "message";
};

#endif
