// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#ifndef MESSAGEBEAN_H
#define MESSAGEBEAN_H

#include <CppBeans.h>

#include <folly/io/IOBuf.h>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class MessageBean {
public:
  MessageBean() = default;

  MessageBean(const char *json)
      : MessageBean(rapidjson::Document{}.Parse(json)) {}

  MessageBean(std::string message) : message(message) {}

  MessageBean(const rapidjson::Value &value) {
    if (value.HasMember(message_label))
      this->message = Typoid<std::string>::FromValue(value[message_label]);
    else
      throw(missing_mandatory_field(message_label));
  }

  void update(MessageBean bean) { message = bean.message; }

  template <typename Writer> void Serialize(Writer &writer) const {
    writer.StartObject();
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

  const char *__name__ = "MessageBean";
  std::string message;
  const char *message_label = "message";
};

#endif
