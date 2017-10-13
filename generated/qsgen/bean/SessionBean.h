// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#ifndef SESSIONBEAN_H
#define SESSIONBEAN_H

#include <CppBeans.h>

#include <folly/io/IOBuf.h>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <qsgen/bean/UserBean.h>

class SessionBean {
public:
  SessionBean() = default;

  SessionBean(const char *json)
      : SessionBean(rapidjson::Document{}.Parse(json)) {}

  SessionBean(std::string token, UserBean user) : token(token), user(user) {}

  SessionBean(const rapidjson::Value &value) {
    if (value.HasMember(token_label))
      this->token = Typoid<std::string>::FromValue(value[token_label]);
    else
      throw(missing_mandatory_field(token_label));
    if (value.HasMember(user_label))
      this->user = Typoid<UserBean>::FromValue(value[user_label]);
    else
      throw(missing_mandatory_field(user_label));
  }

  void update(SessionBean bean) {
    token = bean.token;
    user = bean.user;
  }

  template <typename Writer> void Serialize(Writer &writer) const {
    writer.StartObject();
    writer.String(token_label);
    Typoid<std::string>::Serialize(token, writer);
    writer.String(user_label);
    Typoid<UserBean>::Serialize(user, writer);
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

  const char *__name__ = "SessionBean";
  std::string token;
  const char *token_label = "token";
  UserBean user;
  const char *user_label = "user";
};

#endif
