// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#pragma once

#include <iostream>
#include <string>

#include <folly/Format.h>

#include <SQLiteCpp/SQLiteCpp.h>

#include <CppBeans.h>
#include <qs/database/SqliteTransaction.h>
#include <qs/util/hash.h>
#include <qsgen/bean/MetaBean.h>

template <typename DB, typename T> class DatabaseBean;

using DB = SQLite::Database;

template <> class DatabaseBean<DB, MetaBean> {
public:
  static absl::optional<MetaBean> get(DB *sqliteDatabase, std::string hash) {
    try {
      SQLite::Statement query(*sqliteDatabase,
                              "SELECT * FROM meta WHERE meta_hash = ?");

      query.bind(1, hash);

      while (query.executeStep()) {
        MetaBean bean;

        int getIndex = 0;
        bean.meta_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.author = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.created_at = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.icon = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.meta_type = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.modified_at = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.name = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.source_title = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.source_url = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.text = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.user_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());

        return bean;
      }
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
      return absl::nullopt;
    }
  }

  template <typename FIELD_VALUE>
  static List<MetaBean> get_by(DB *sqliteDatabase, std::string field,
                               FIELD_VALUE field_value) {
    List<MetaBean> result(0);

    try {
      std::string query_str =
          folly::format("SELECT * FROM meta WHERE {} = ?", field.c_str()).str();
      SQLite::Statement query(*sqliteDatabase, query_str.c_str());

      query.bind(1, field_value);

      while (query.executeStep()) {
        MetaBean bean;

        int getIndex = 0;
        bean.meta_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.author = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.created_at = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.icon = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.meta_type = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.modified_at = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.name = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.source_title = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.source_url = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.text = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.user_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());

        result.push_back(bean);
      }
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
      return result;
    }

    return result;
  }

  static void remove(DB *sqliteDatabase, std::string hash) {
    try {
      SQLite::Statement query(*sqliteDatabase,
                              "DELETE FROM meta WHERE meta_hash = ?");

      query.bind(1, hash);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  template <typename FIELD_VALUE>
  static void remove_by(DB *sqliteDatabase, std::string field,
                        FIELD_VALUE field_value) {
    try {
      std::string query_str =
          folly::format("DELETE FROM meta WHERE {} = ?", field.c_str()).str();
      SQLite::Statement query(*sqliteDatabase, query_str.c_str());

      query.bind(1, field_value);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static List<MetaBean> sql(DB *sqliteDatabase, std::string sql) {
    List<MetaBean> result(0);

    try {
      SQLite::Statement query(*sqliteDatabase, sql.c_str());

      while (query.executeStep()) {
        MetaBean bean;
        int getIndex = 0;

        bean.meta_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.author = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.created_at = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.icon = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.meta_type = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.modified_at = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.name = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.source_title = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.source_url = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.text = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.user_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());

        result.push_back(bean);
      }
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
      return result;
    }

    return result;
  }

  static std::string insert(DB *sqliteDatabase, MetaBean bean) {
    try {
      SQLite::Statement query(
          *sqliteDatabase,
          "INSERT INTO meta ('meta_hash', 'author', 'created_at', 'icon', "
          "'meta_type', 'modified_at', 'name', 'source_title', 'source_url', "
          "'text', 'user_hash') VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

      int bindIndex = 1;
      if (!bean.meta_hash)
        bean.meta_hash = qs::util::Hash::get();
      if (bean.meta_hash)
        query.bind(bindIndex++, *bean.meta_hash);
      else
        query.bind(bindIndex++);
      if (bean.author)
        query.bind(bindIndex++, *bean.author);
      else
        query.bind(bindIndex++);
      if (bean.created_at)
        query.bind(bindIndex++, *bean.created_at);
      else
        query.bind(bindIndex++);
      if (bean.icon)
        query.bind(bindIndex++, *bean.icon);
      else
        query.bind(bindIndex++);
      if (bean.meta_type)
        query.bind(bindIndex++, *bean.meta_type);
      else
        query.bind(bindIndex++);
      if (bean.modified_at)
        query.bind(bindIndex++, *bean.modified_at);
      else
        query.bind(bindIndex++);
      if (bean.name)
        query.bind(bindIndex++, *bean.name);
      else
        query.bind(bindIndex++);
      if (bean.source_title)
        query.bind(bindIndex++, *bean.source_title);
      else
        query.bind(bindIndex++);
      if (bean.source_url)
        query.bind(bindIndex++, *bean.source_url);
      else
        query.bind(bindIndex++);
      if (bean.text)
        query.bind(bindIndex++, *bean.text);
      else
        query.bind(bindIndex++);
      if (bean.user_hash)
        query.bind(bindIndex++, *bean.user_hash);
      else
        query.bind(bindIndex++);

      query.exec();

      return *bean.meta_hash;
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void insert_with_pk(DB *sqliteDatabase, MetaBean bean) {
    try {
      SQLite::Statement query(
          *sqliteDatabase,
          "INSERT INTO meta ('meta_hash', 'author', 'created_at', 'icon', "
          "'meta_type', 'modified_at', 'name', 'source_title', 'source_url', "
          "'text', 'user_hash') VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

      int bindIndex = 1;
      if (bean.meta_hash)
        query.bind(bindIndex++, *bean.meta_hash);
      else
        query.bind(bindIndex++);
      if (bean.author)
        query.bind(bindIndex++, *bean.author);
      else
        query.bind(bindIndex++);
      if (bean.created_at)
        query.bind(bindIndex++, *bean.created_at);
      else
        query.bind(bindIndex++);
      if (bean.icon)
        query.bind(bindIndex++, *bean.icon);
      else
        query.bind(bindIndex++);
      if (bean.meta_type)
        query.bind(bindIndex++, *bean.meta_type);
      else
        query.bind(bindIndex++);
      if (bean.modified_at)
        query.bind(bindIndex++, *bean.modified_at);
      else
        query.bind(bindIndex++);
      if (bean.name)
        query.bind(bindIndex++, *bean.name);
      else
        query.bind(bindIndex++);
      if (bean.source_title)
        query.bind(bindIndex++, *bean.source_title);
      else
        query.bind(bindIndex++);
      if (bean.source_url)
        query.bind(bindIndex++, *bean.source_url);
      else
        query.bind(bindIndex++);
      if (bean.text)
        query.bind(bindIndex++, *bean.text);
      else
        query.bind(bindIndex++);
      if (bean.user_hash)
        query.bind(bindIndex++, *bean.user_hash);
      else
        query.bind(bindIndex++);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void update(DB *sqliteDatabase, MetaBean bean) {
    try {
      std::string setBuilder = "";
      if (bean.author) {
        setBuilder +=
            ((setBuilder != "") ? std::string(", ") : std::string("")) +
            std::string("author = ?");
      }
      if (bean.created_at) {
        setBuilder +=
            ((setBuilder != "") ? std::string(", ") : std::string("")) +
            std::string("created_at = ?");
      }
      if (bean.icon) {
        setBuilder +=
            ((setBuilder != "") ? std::string(", ") : std::string("")) +
            std::string("icon = ?");
      }
      if (bean.meta_type) {
        setBuilder +=
            ((setBuilder != "") ? std::string(", ") : std::string("")) +
            std::string("meta_type = ?");
      }
      if (bean.modified_at) {
        setBuilder +=
            ((setBuilder != "") ? std::string(", ") : std::string("")) +
            std::string("modified_at = ?");
      }
      if (bean.name) {
        setBuilder +=
            ((setBuilder != "") ? std::string(", ") : std::string("")) +
            std::string("name = ?");
      }
      if (bean.source_title) {
        setBuilder +=
            ((setBuilder != "") ? std::string(", ") : std::string("")) +
            std::string("source_title = ?");
      }
      if (bean.source_url) {
        setBuilder +=
            ((setBuilder != "") ? std::string(", ") : std::string("")) +
            std::string("source_url = ?");
      }
      if (bean.text) {
        setBuilder +=
            ((setBuilder != "") ? std::string(", ") : std::string("")) +
            std::string("text = ?");
      }
      if (bean.user_hash) {
        setBuilder +=
            ((setBuilder != "") ? std::string(", ") : std::string("")) +
            std::string("user_hash = ?");
      }
      std::string query_template =
          folly::format("UPDATE meta SET {} WHERE meta_hash = ?",
                        setBuilder.c_str())
              .str();
      SQLite::Statement query(*sqliteDatabase, query_template.c_str());

      int bindIndex = 1;
      if (bean.author)
        query.bind(bindIndex++, *bean.author);
      if (bean.created_at)
        query.bind(bindIndex++, *bean.created_at);
      if (bean.icon)
        query.bind(bindIndex++, *bean.icon);
      if (bean.meta_type)
        query.bind(bindIndex++, *bean.meta_type);
      if (bean.modified_at)
        query.bind(bindIndex++, *bean.modified_at);
      if (bean.name)
        query.bind(bindIndex++, *bean.name);
      if (bean.source_title)
        query.bind(bindIndex++, *bean.source_title);
      if (bean.source_url)
        query.bind(bindIndex++, *bean.source_url);
      if (bean.text)
        query.bind(bindIndex++, *bean.text);
      if (bean.user_hash)
        query.bind(bindIndex++, *bean.user_hash);

      query.bind(bindIndex++, *bean.meta_hash);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void override(DB *sqliteDatabase, MetaBean bean) {
    try {
      SQLite::Statement query(
          *sqliteDatabase,
          "UPDATE meta SET meta_hash = ?, author = ?, created_at = ?, icon = "
          "?, meta_type = ?, modified_at = ?, name = ?, source_title = ?, "
          "source_url = ?, text = ?, user_hash = ? WHERE meta_hash = ?");

      int bindIndex = 1;

      if (bean.author)
        query.bind(bindIndex++, *bean.author);
      else
        query.bind(bindIndex++);
      if (bean.created_at)
        query.bind(bindIndex++, *bean.created_at);
      else
        query.bind(bindIndex++);
      if (bean.icon)
        query.bind(bindIndex++, *bean.icon);
      else
        query.bind(bindIndex++);
      if (bean.meta_type)
        query.bind(bindIndex++, *bean.meta_type);
      else
        query.bind(bindIndex++);
      if (bean.modified_at)
        query.bind(bindIndex++, *bean.modified_at);
      else
        query.bind(bindIndex++);
      if (bean.name)
        query.bind(bindIndex++, *bean.name);
      else
        query.bind(bindIndex++);
      if (bean.source_title)
        query.bind(bindIndex++, *bean.source_title);
      else
        query.bind(bindIndex++);
      if (bean.source_url)
        query.bind(bindIndex++, *bean.source_url);
      else
        query.bind(bindIndex++);
      if (bean.text)
        query.bind(bindIndex++, *bean.text);
      else
        query.bind(bindIndex++);
      if (bean.user_hash)
        query.bind(bindIndex++, *bean.user_hash);
      else
        query.bind(bindIndex++);

      query.bind(bindIndex++, *bean.meta_hash);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }
};
