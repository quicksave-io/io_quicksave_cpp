// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#ifndef TAGBEAN_H
#define TAGBEAN_H

#include <CppBeans.h>

#include <folly/io/IOBuf.h>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class TagBean {
public:
  TagBean() = default;

  TagBean(const char *json) : TagBean(rapidjson::Document{}.Parse(json)) {}

  TagBean(absl::optional<std::string> tag_hash,
          absl::optional<std::string> meta_hash,
          absl::optional<std::string> name,
          absl::optional<std::string> user_hash,
          absl::optional<std::string> value)
      : tag_hash(tag_hash), meta_hash(meta_hash), name(name),
        user_hash(user_hash), value(value) {}

  TagBean(const rapidjson::Value &value) {
    if (value.HasMember(tag_hash_label))
      this->tag_hash = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[tag_hash_label]));
    if (value.HasMember(meta_hash_label))
      this->meta_hash = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[meta_hash_label]));
    if (value.HasMember(name_label))
      this->name = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[name_label]));
    if (value.HasMember(user_hash_label))
      this->user_hash = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[user_hash_label]));
    if (value.HasMember(value_label))
      this->value = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[value_label]));
  }

  void update(TagBean bean) {
    if (bean.tag_hash)
      tag_hash = bean.tag_hash;
    if (bean.meta_hash)
      meta_hash = bean.meta_hash;
    if (bean.name)
      name = bean.name;
    if (bean.user_hash)
      user_hash = bean.user_hash;
    if (bean.value)
      value = bean.value;
  }

  template <typename Writer> void Serialize(Writer &writer) const {
    writer.StartObject();
    if (tag_hash)
      writer.String(tag_hash_label);
    if (tag_hash)
      Typoid<std::string>::Serialize(*tag_hash, writer);
    if (meta_hash)
      writer.String(meta_hash_label);
    if (meta_hash)
      Typoid<std::string>::Serialize(*meta_hash, writer);
    if (name)
      writer.String(name_label);
    if (name)
      Typoid<std::string>::Serialize(*name, writer);
    if (user_hash)
      writer.String(user_hash_label);
    if (user_hash)
      Typoid<std::string>::Serialize(*user_hash, writer);
    if (value)
      writer.String(value_label);
    if (value)
      Typoid<std::string>::Serialize(*value, writer);
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

  const char *__name__ = "TagBean";
  absl::optional<std::string> tag_hash;
  const char *tag_hash_label = "tag_hash";
  absl::optional<std::string> meta_hash;
  const char *meta_hash_label = "meta_hash";
  absl::optional<std::string> name;
  const char *name_label = "name";
  absl::optional<std::string> user_hash;
  const char *user_hash_label = "user_hash";
  absl::optional<std::string> value;
  const char *value_label = "value";
};

#endif
