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
#include <qsgen/bean/KeyBean.h>

template <typename DB, typename T> class DatabaseBean;

using DB = SQLite::Database;

template <> class DatabaseBean<DB, KeyBean> {
public:
  static absl::optional<KeyBean> get(DB *sqliteDatabase, std::string hash) {
    try {
      SQLite::Statement query(*sqliteDatabase,
                              "SELECT * FROM key WHERE key_hash = ?");

      query.bind(1, hash);

      while (query.executeStep()) {
        KeyBean bean;

        int getIndex = 0;
        bean.key_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.name = query.getColumn(getIndex++).getString();
        bean.user_hash = query.getColumn(getIndex++).getString();
        bean.value = query.getColumn(getIndex++).getString();

        return bean;
      }
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
      return absl::nullopt;
    }
  }

  template <typename FIELD_VALUE>
  static List<KeyBean> get_by(DB *sqliteDatabase, std::string field,
                              FIELD_VALUE field_value) {
    List<KeyBean> result(0);

    try {
      std::string query_str =
          folly::format("SELECT * FROM key WHERE {} = ?", field.c_str()).str();
      SQLite::Statement query(*sqliteDatabase, query_str.c_str());

      query.bind(1, field_value);

      while (query.executeStep()) {
        KeyBean bean;

        int getIndex = 0;
        bean.key_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.name = query.getColumn(getIndex++).getString();
        bean.user_hash = query.getColumn(getIndex++).getString();
        bean.value = query.getColumn(getIndex++).getString();

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
                              "DELETE FROM key WHERE key_hash = ?");

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
          folly::format("DELETE FROM key WHERE {} = ?", field.c_str()).str();
      SQLite::Statement query(*sqliteDatabase, query_str.c_str());

      query.bind(1, field_value);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static List<KeyBean> sql(DB *sqliteDatabase, std::string sql) {
    List<KeyBean> result(0);

    try {
      SQLite::Statement query(*sqliteDatabase, sql.c_str());

      while (query.executeStep()) {
        KeyBean bean;
        int getIndex = 0;

        bean.key_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.name = query.getColumn(getIndex++).getString();
        bean.user_hash = query.getColumn(getIndex++).getString();
        bean.value = query.getColumn(getIndex++).getString();

        result.push_back(bean);
      }
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
      return result;
    }

    return result;
  }

  static std::string insert(DB *sqliteDatabase, KeyBean bean) {
    try {
      SQLite::Statement query(*sqliteDatabase, "INSERT INTO key ('key_hash', "
                                               "'name', 'user_hash', 'value') "
                                               "VALUES (?, ?, ?, ?)");

      int bindIndex = 1;
      if (!bean.key_hash)
        bean.key_hash = qs::util::Hash::get();
      if (bean.key_hash)
        query.bind(bindIndex++, *bean.key_hash);
      else
        query.bind(bindIndex++);
      query.bind(bindIndex++, bean.name);
      query.bind(bindIndex++, bean.user_hash);
      query.bind(bindIndex++, bean.value);

      query.exec();

      return *bean.key_hash;
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void insert_with_pk(DB *sqliteDatabase, KeyBean bean) {
    try {
      SQLite::Statement query(*sqliteDatabase, "INSERT INTO key ('key_hash', "
                                               "'name', 'user_hash', 'value') "
                                               "VALUES (?, ?, ?, ?)");

      int bindIndex = 1;
      if (bean.key_hash)
        query.bind(bindIndex++, *bean.key_hash);
      else
        query.bind(bindIndex++);
      query.bind(bindIndex++, bean.name);
      query.bind(bindIndex++, bean.user_hash);
      query.bind(bindIndex++, bean.value);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void update(DB *sqliteDatabase, KeyBean bean) {
    try {
      std::string setBuilder = "";
      setBuilder += ((setBuilder != "") ? std::string(", ") : std::string("")) +
                    std::string("name = ?");
      setBuilder += ((setBuilder != "") ? std::string(", ") : std::string("")) +
                    std::string("user_hash = ?");
      setBuilder += ((setBuilder != "") ? std::string(", ") : std::string("")) +
                    std::string("value = ?");
      std::string query_template =
          folly::format("UPDATE key SET {} WHERE key_hash = ?",
                        setBuilder.c_str())
              .str();
      SQLite::Statement query(*sqliteDatabase, query_template.c_str());

      int bindIndex = 1;
      query.bind(bindIndex++, bean.name);
      query.bind(bindIndex++, bean.user_hash);
      query.bind(bindIndex++, bean.value);

      query.bind(bindIndex++, *bean.key_hash);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void override(DB *sqliteDatabase, KeyBean bean) {
    try {
      SQLite::Statement query(*sqliteDatabase, "UPDATE key SET key_hash = ?, "
                                               "name = ?, user_hash = ?, value "
                                               "= ? WHERE key_hash = ?");

      int bindIndex = 1;

      query.bind(bindIndex++, bean.name);
      query.bind(bindIndex++, bean.user_hash);
      query.bind(bindIndex++, bean.value);

      query.bind(bindIndex++, *bean.key_hash);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }
};
