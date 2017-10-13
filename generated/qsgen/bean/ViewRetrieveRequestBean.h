// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#ifndef VIEWRETRIEVEREQUESTBEAN_H
#define VIEWRETRIEVEREQUESTBEAN_H

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <CppBeans.h>
#include <folly/io/IOBuf.h>
#include <memory>

class ViewRetrieveRequestBean {
public:
  ViewRetrieveRequestBean() = default;

  ViewRetrieveRequestBean(const char *json)
      : ViewRetrieveRequestBean(rapidjson::Document{}.Parse(json)) {}

  ViewRetrieveRequestBean(std::string view_hash) : view_hash(view_hash) {}

  ViewRetrieveRequestBean(const rapidjson::Value &value) {
    if (value.HasMember(view_hash_label))
      this->view_hash = Typoid<std::string>::FromValue(value[view_hash_label]);
    else
      throw(missing_mandatory_field(view_hash_label));
  }

  void update(ViewRetrieveRequestBean bean) { view_hash = bean.view_hash; }

  template <typename Writer> void Serialize(Writer &writer) const {
    writer.StartObject();
    writer.String(view_hash_label);
    Typoid<std::string>::Serialize(view_hash, writer);
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

  const char *__name__ = "ViewRetrieveRequestBean";
  std::string view_hash;
  const char *view_hash_label = "view_hash";
};

#endif