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
#include <qsgen/bean/ActionBean.h>

template <typename DB, typename T> class DatabaseBean;

using DB = SQLite::Database;

template <> class DatabaseBean<DB, ActionBean> {
public:
  static absl::optional<ActionBean> get(DB *sqliteDatabase, std::string hash) {
    try {
      SQLite::Statement query(*sqliteDatabase,
                              "SELECT * FROM action WHERE action_hash = ?");

      query.bind(1, hash);

      while (query.executeStep()) {
        ActionBean bean;

        int getIndex = 0;
        bean.action_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.kwargs = query.getColumn(getIndex++).getString().c_str();
        bean.meta_hash = query.getColumn(getIndex++).getString();
        bean.name = query.getColumn(getIndex++).getString();

        return bean;
      }
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
      return absl::nullopt;
    }
  }

  template <typename FIELD_VALUE>
  static List<ActionBean> get_by(DB *sqliteDatabase, std::string field,
                                 FIELD_VALUE field_value) {
    List<ActionBean> result(0);

    try {
      std::string query_str =
          folly::format("SELECT * FROM action WHERE {} = ?", field.c_str())
              .str();
      SQLite::Statement query(*sqliteDatabase, query_str.c_str());

      query.bind(1, field_value);

      while (query.executeStep()) {
        ActionBean bean;

        int getIndex = 0;
        bean.action_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.kwargs = query.getColumn(getIndex++).getString().c_str();
        bean.meta_hash = query.getColumn(getIndex++).getString();
        bean.name = query.getColumn(getIndex++).getString();

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
                              "DELETE FROM action WHERE action_hash = ?");

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
          folly::format("DELETE FROM action WHERE {} = ?", field.c_str()).str();
      SQLite::Statement query(*sqliteDatabase, query_str.c_str());

      query.bind(1, field_value);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static List<ActionBean> sql(DB *sqliteDatabase, std::string sql) {
    List<ActionBean> result(0);

    try {
      SQLite::Statement query(*sqliteDatabase, sql.c_str());

      while (query.executeStep()) {
        ActionBean bean;
        int getIndex = 0;

        bean.action_hash = absl::make_optional<std::string>(
            query.getColumn(getIndex++).getString());
        bean.kwargs = query.getColumn(getIndex++).getString().c_str();
        bean.meta_hash = query.getColumn(getIndex++).getString();
        bean.name = query.getColumn(getIndex++).getString();

        result.push_back(bean);
      }
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
      return result;
    }

    return result;
  }

  static std::string insert(DB *sqliteDatabase, ActionBean bean) {
    try {
      SQLite::Statement query(*sqliteDatabase,
                              "INSERT INTO action ('action_hash', 'kwargs', "
                              "'meta_hash', 'name') VALUES (?, ?, ?, ?)");

      int bindIndex = 1;
      if (!bean.action_hash)
        bean.action_hash = qs::util::Hash::get();
      if (bean.action_hash)
        query.bind(bindIndex++, *bean.action_hash);
      else
        query.bind(bindIndex++);
      query.bind(bindIndex++, bean.kwargs);
      query.bind(bindIndex++, bean.meta_hash);
      query.bind(bindIndex++, bean.name);

      query.exec();

      return *bean.action_hash;
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void insert_with_pk(DB *sqliteDatabase, ActionBean bean) {
    try {
      SQLite::Statement query(*sqliteDatabase,
                              "INSERT INTO action ('action_hash', 'kwargs', "
                              "'meta_hash', 'name') VALUES (?, ?, ?, ?)");

      int bindIndex = 1;
      if (bean.action_hash)
        query.bind(bindIndex++, *bean.action_hash);
      else
        query.bind(bindIndex++);
      query.bind(bindIndex++, bean.kwargs);
      query.bind(bindIndex++, bean.meta_hash);
      query.bind(bindIndex++, bean.name);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void update(DB *sqliteDatabase, ActionBean bean) {
    try {
      std::string setBuilder = "";
      setBuilder += ((setBuilder != "") ? std::string(", ") : std::string("")) +
                    std::string("kwargs = ?");
      setBuilder += ((setBuilder != "") ? std::string(", ") : std::string("")) +
                    std::string("meta_hash = ?");
      setBuilder += ((setBuilder != "") ? std::string(", ") : std::string("")) +
                    std::string("name = ?");
      std::string query_template =
          folly::format("UPDATE action SET {} WHERE action_hash = ?",
                        setBuilder.c_str())
              .str();
      SQLite::Statement query(*sqliteDatabase, query_template.c_str());

      int bindIndex = 1;
      query.bind(bindIndex++, bean.kwargs);
      query.bind(bindIndex++, bean.meta_hash);
      query.bind(bindIndex++, bean.name);

      query.bind(bindIndex++, *bean.action_hash);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void override(DB *sqliteDatabase, ActionBean bean) {
    try {
      SQLite::Statement query(*sqliteDatabase,
                              "UPDATE action SET action_hash = ?, kwargs = ?, "
                              "meta_hash = ?, name = ? WHERE action_hash = ?");

      int bindIndex = 1;

      query.bind(bindIndex++, bean.kwargs);
      query.bind(bindIndex++, bean.meta_hash);
      query.bind(bindIndex++, bean.name);

      query.bind(bindIndex++, *bean.action_hash);

      query.exec();
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }
};
