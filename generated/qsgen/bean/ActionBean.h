// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#ifndef ACTIONBEAN_H
#define ACTIONBEAN_H

#include <CppBeans.h>

#include <folly/io/IOBuf.h>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class ActionBean {
public:
  ActionBean() = default;

  ActionBean(const char *json)
      : ActionBean(rapidjson::Document{}.Parse(json)) {}

  ActionBean(absl::optional<std::string> action_hash, SerializedDict kwargs,
             std::string meta_hash, std::string name)
      : action_hash(action_hash), kwargs(kwargs), meta_hash(meta_hash),
        name(name) {}

  ActionBean(const rapidjson::Value &value) {
    if (value.HasMember(action_hash_label))
      this->action_hash = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[action_hash_label]));
    if (value.HasMember(kwargs_label))
      this->kwargs = Typoid<SerializedDict>::FromValue(value[kwargs_label]);
    else
      throw(missing_mandatory_field(kwargs_label));
    if (value.HasMember(meta_hash_label))
      this->meta_hash = Typoid<std::string>::FromValue(value[meta_hash_label]);
    else
      throw(missing_mandatory_field(meta_hash_label));
    if (value.HasMember(name_label))
      this->name = Typoid<std::string>::FromValue(value[name_label]);
    else
      throw(missing_mandatory_field(name_label));
  }

  void update(ActionBean bean) {
    if (bean.action_hash)
      action_hash = bean.action_hash;
    kwargs = bean.kwargs;
    meta_hash = bean.meta_hash;
    name = bean.name;
  }

  template <typename Writer> void Serialize(Writer &writer) const {
    writer.StartObject();
    if (action_hash)
      writer.String(action_hash_label);
    if (action_hash)
      Typoid<std::string>::Serialize(*action_hash, writer);
    writer.String(kwargs_label);
    Typoid<SerializedDict>::Serialize(kwargs, writer);
    writer.String(meta_hash_label);
    Typoid<std::string>::Serialize(meta_hash, writer);
    writer.String(name_label);
    Typoid<std::string>::Serialize(name, writer);
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

  const char *__name__ = "ActionBean";
  absl::optional<std::string> action_hash;
  const char *action_hash_label = "action_hash";
  SerializedDict kwargs;
  const char *kwargs_label = "kwargs";
  std::string meta_hash;
  const char *meta_hash_label = "meta_hash";
  std::string name;
  const char *name_label = "name";
};

#endif
