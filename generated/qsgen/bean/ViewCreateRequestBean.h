// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#ifndef VIEWCREATEREQUESTBEAN_H
#define VIEWCREATEREQUESTBEAN_H

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include <CppBeans.h>
#include <folly/io/IOBuf.h>
#include <memory>

#include <generated/qsgen/bean/ViewBean.h>

class ViewCreateRequestBean {
public:
  ViewCreateRequestBean() = default;

  ViewCreateRequestBean(const char *json)
      : ViewCreateRequestBean(rapidjson::Document{}.Parse(json)) {}

  ViewCreateRequestBean(ViewBean view) : view(view) {}

  ViewCreateRequestBean(const rapidjson::Value &value) {
    if (value.HasMember(view_label))
      this->view = Typoid<ViewBean>::FromValue(value[view_label]);
    else
      throw(missing_mandatory_field(view_label));
  }

  void update(ViewCreateRequestBean bean) { view = bean.view; }

  template <typename Writer> void Serialize(Writer &writer) const {
    writer.StartObject();
    writer.String(view_label);
    Typoid<ViewBean>::Serialize(view, writer);
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

  const char *__name__ = "ViewCreateRequestBean";
  ViewBean view;
  const char *view_label = "view";
};

#endif
