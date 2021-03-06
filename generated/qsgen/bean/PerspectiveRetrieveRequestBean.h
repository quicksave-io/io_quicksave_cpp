// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#ifndef PERSPECTIVERETRIEVEREQUESTBEAN_H
#define PERSPECTIVERETRIEVEREQUESTBEAN_H

#include <CppBeans.h>

#include <folly/io/IOBuf.h>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class PerspectiveRetrieveRequestBean {
public:
  PerspectiveRetrieveRequestBean() = default;

  PerspectiveRetrieveRequestBean(const char *json)
      : PerspectiveRetrieveRequestBean(rapidjson::Document{}.Parse(json)) {}

  PerspectiveRetrieveRequestBean(
      absl::optional<List<std::string>> perspective_hash, std::string variant)
      : perspective_hash(perspective_hash), variant(variant) {}

  PerspectiveRetrieveRequestBean(const rapidjson::Value &value) {
    if (value.HasMember(perspective_hash_label))
      this->perspective_hash = absl::make_optional<List<std::string>>(
          Typoid<List<std::string>>::FromValue(value[perspective_hash_label]));
    if (value.HasMember(variant_label))
      this->variant = Typoid<std::string>::FromValue(value[variant_label]);
    else
      throw(missing_mandatory_field(variant_label));
  }

  void update(PerspectiveRetrieveRequestBean bean) {
    if (bean.perspective_hash)
      perspective_hash = bean.perspective_hash;
    variant = bean.variant;
  }

  template <typename Writer> void Serialize(Writer &writer) const {
    writer.StartObject();
    if (perspective_hash)
      writer.String(perspective_hash_label);
    if (perspective_hash)
      Typoid<List<std::string>>::Serialize(*perspective_hash, writer);
    writer.String(variant_label);
    Typoid<std::string>::Serialize(variant, writer);
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

  const char *__name__ = "PerspectiveRetrieveRequestBean";
  absl::optional<List<std::string>> perspective_hash;
  const char *perspective_hash_label = "perspective_hash";
  std::string variant;
  const char *variant_label = "variant";
};

#endif
