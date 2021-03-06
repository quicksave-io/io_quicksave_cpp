// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#ifndef PERSPECTIVEBEAN_H
#define PERSPECTIVEBEAN_H

#include <CppBeans.h>

#include <folly/io/IOBuf.h>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class PerspectiveBean {
public:
  PerspectiveBean() = default;

  PerspectiveBean(const char *json)
      : PerspectiveBean(rapidjson::Document{}.Parse(json)) {}

  PerspectiveBean(absl::optional<std::string> perspective_hash,
                  std::string defined_query, std::string name,
                  absl::optional<std::string> ordering,
                  absl::optional<std::string> refined_query,
                  absl::optional<std::string> user_hash)
      : perspective_hash(perspective_hash), defined_query(defined_query),
        name(name), ordering(ordering), refined_query(refined_query),
        user_hash(user_hash) {}

  PerspectiveBean(const rapidjson::Value &value) {
    if (value.HasMember(perspective_hash_label))
      this->perspective_hash = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[perspective_hash_label]));
    if (value.HasMember(defined_query_label))
      this->defined_query =
          Typoid<std::string>::FromValue(value[defined_query_label]);
    else
      throw(missing_mandatory_field(defined_query_label));
    if (value.HasMember(name_label))
      this->name = Typoid<std::string>::FromValue(value[name_label]);
    else
      throw(missing_mandatory_field(name_label));
    if (value.HasMember(ordering_label))
      this->ordering = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[ordering_label]));
    if (value.HasMember(refined_query_label))
      this->refined_query = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[refined_query_label]));
    if (value.HasMember(user_hash_label))
      this->user_hash = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[user_hash_label]));
  }

  void update(PerspectiveBean bean) {
    if (bean.perspective_hash)
      perspective_hash = bean.perspective_hash;
    defined_query = bean.defined_query;
    name = bean.name;
    if (bean.ordering)
      ordering = bean.ordering;
    if (bean.refined_query)
      refined_query = bean.refined_query;
    if (bean.user_hash)
      user_hash = bean.user_hash;
  }

  template <typename Writer> void Serialize(Writer &writer) const {
    writer.StartObject();
    if (perspective_hash)
      writer.String(perspective_hash_label);
    if (perspective_hash)
      Typoid<std::string>::Serialize(*perspective_hash, writer);
    writer.String(defined_query_label);
    Typoid<std::string>::Serialize(defined_query, writer);
    writer.String(name_label);
    Typoid<std::string>::Serialize(name, writer);
    if (ordering)
      writer.String(ordering_label);
    if (ordering)
      Typoid<std::string>::Serialize(*ordering, writer);
    if (refined_query)
      writer.String(refined_query_label);
    if (refined_query)
      Typoid<std::string>::Serialize(*refined_query, writer);
    if (user_hash)
      writer.String(user_hash_label);
    if (user_hash)
      Typoid<std::string>::Serialize(*user_hash, writer);
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

  const char *__name__ = "PerspectiveBean";
  absl::optional<std::string> perspective_hash;
  const char *perspective_hash_label = "perspective_hash";
  std::string defined_query;
  const char *defined_query_label = "defined_query";
  std::string name;
  const char *name_label = "name";
  absl::optional<std::string> ordering;
  const char *ordering_label = "ordering";
  absl::optional<std::string> refined_query;
  const char *refined_query_label = "refined_query";
  absl::optional<std::string> user_hash;
  const char *user_hash_label = "user_hash";
};

#endif
