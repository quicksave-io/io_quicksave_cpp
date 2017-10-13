// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#ifndef FILEBEAN_H
#define FILEBEAN_H

#include <CppBeans.h>

#include <folly/io/IOBuf.h>
#include <memory>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class FileBean {
public:
  FileBean() = default;

  FileBean(const char *json) : FileBean(rapidjson::Document{}.Parse(json)) {}

  FileBean(absl::optional<std::string> file_hash, std::string filename,
           int filesize, std::string meta_hash, std::string mimetype)
      : file_hash(file_hash), filename(filename), filesize(filesize),
        meta_hash(meta_hash), mimetype(mimetype) {}

  FileBean(const rapidjson::Value &value) {
    if (value.HasMember(file_hash_label))
      this->file_hash = absl::make_optional<std::string>(
          Typoid<std::string>::FromValue(value[file_hash_label]));
    if (value.HasMember(filename_label))
      this->filename = Typoid<std::string>::FromValue(value[filename_label]);
    else
      throw(missing_mandatory_field(filename_label));
    if (value.HasMember(filesize_label))
      this->filesize = Typoid<int>::FromValue(value[filesize_label]);
    else
      throw(missing_mandatory_field(filesize_label));
    if (value.HasMember(meta_hash_label))
      this->meta_hash = Typoid<std::string>::FromValue(value[meta_hash_label]);
    else
      throw(missing_mandatory_field(meta_hash_label));
    if (value.HasMember(mimetype_label))
      this->mimetype = Typoid<std::string>::FromValue(value[mimetype_label]);
    else
      throw(missing_mandatory_field(mimetype_label));
  }

  void update(FileBean bean) {
    if (bean.file_hash)
      file_hash = bean.file_hash;
    filename = bean.filename;
    filesize = bean.filesize;
    meta_hash = bean.meta_hash;
    mimetype = bean.mimetype;
  }

  template <typename Writer> void Serialize(Writer &writer) const {
    writer.StartObject();
    if (file_hash)
      writer.String(file_hash_label);
    if (file_hash)
      Typoid<std::string>::Serialize(*file_hash, writer);
    writer.String(filename_label);
    Typoid<std::string>::Serialize(filename, writer);
    writer.String(filesize_label);
    Typoid<int>::Serialize(filesize, writer);
    writer.String(meta_hash_label);
    Typoid<std::string>::Serialize(meta_hash, writer);
    writer.String(mimetype_label);
    Typoid<std::string>::Serialize(mimetype, writer);
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

  const char *__name__ = "FileBean";
  absl::optional<std::string> file_hash;
  const char *file_hash_label = "file_hash";
  std::string filename;
  const char *filename_label = "filename";
  int filesize;
  const char *filesize_label = "filesize";
  std::string meta_hash;
  const char *meta_hash_label = "meta_hash";
  std::string mimetype;
  const char *mimetype_label = "mimetype";
};

#endif
