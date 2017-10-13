// This file is an AUTOGENERATED part of beans project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#pragma once

#include <CppBeans.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <database/PostgresTransaction.h>
#include <qs/util/hash.h>
#include <iostream>
#include <string>
#include <util/format.h>

#include <generated/qsgen/bean/KeyBean.h>

template <typename DB, typename T> class DatabaseBean;

using PostgresTransactionImpl = tao::postgres::transaction;

template <> class DatabaseBean<PostgresTransactionImpl, KeyBean> {
public:
  static std::optional<KeyBean> get(PostgresTransactionImpl *tr,
                                    std::string hash) {
    try {
      const char *query = "SELECT * FROM public.key WHERE key_hash = $1";

      auto result = tr->execute(query, hash);
      auto row = result[0];

      KeyBean bean;

      int getIndex = 0;

      bean.key_hash =
          std::make_optional<std::string>(row.get<std::string>(getIndex++));
      bean.name = row.get<std::string>(getIndex++);
      bean.user_hash = row.get<std::string>(getIndex++);
      bean.value = row.get<std::string>(getIndex++);

      return bean;
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
      return std::none;
    }
  }

  template <typename FIELD_VALUE>
  static List<KeyBean> get_by(PostgresTransactionImpl *tr, std::string field,
                              FIELD_VALUE field_value) {
    List<KeyBean> result(0);

    try {
      std::string query_str = Format::format(
          "SELECT * FROM public.key WHERE %s = $1", field.c_str());
      const char *query = query_str.c_str();

      auto query_result = tr->execute(query, field_value);

      for (int rowIndex = 0; rowIndex < query_result.size(); ++rowIndex) {
        auto row = query_result.at(rowIndex);

        KeyBean bean;

        int getIndex = 0;

        bean.key_hash =
            std::make_optional<std::string>(row.get<std::string>(getIndex++));
        bean.name = row.get<std::string>(getIndex++);
        bean.user_hash = row.get<std::string>(getIndex++);
        bean.value = row.get<std::string>(getIndex++);

        result.push_back(bean);
      }
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
      return result;
    }

    return result;
  }

  static void remove(PostgresTransactionImpl *tr, std::string hash) {
    try {
      const char *query = "DELETE FROM public.key WHERE key_hash = $1";

      tr->execute(query, hash);
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  template <typename FIELD_VALUE>
  static void remove_by(PostgresTransactionImpl *tr, std::string field,
                        FIELD_VALUE field_value) {
    try {
      std::string query_str =
          Format::format("DELETE FROM public.key WHERE %s = $1", field.c_str());
      const char *query = query_str.c_str();

      tr->execute(query, field_value);
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static List<KeyBean> sql(PostgresTransactionImpl *tr, std::string sql) {
    List<KeyBean> result(0);

    try {
      const char *query = sql.c_str();

      auto query_result = tr->execute(query);

      for (int rowIndex = 0; rowIndex < query_result.size(); ++rowIndex) {
        auto row = query_result.at(rowIndex);

        KeyBean bean;

        int getIndex = 0;

        bean.key_hash =
            std::make_optional<std::string>(row.get<std::string>(getIndex++));
        bean.name = row.get<std::string>(getIndex++);
        bean.user_hash = row.get<std::string>(getIndex++);
        bean.value = row.get<std::string>(getIndex++);

        result.push_back(bean);
      }
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
      return result;
    }

    return result;
  }

  static std::string insert(PostgresTransactionImpl *tr, KeyBean bean) {
    try {
      const char *query = "INSERT INTO public.key (\"key_hash\", \"name\", "
                          "\"user_hash\", \"value\") VALUES ($1, $2, $3, $4)";

      int bindIndex = 1;
      if (!bean.key_hash)
        bean.key_hash = Hash::get();

      tr->execute(query, ((bean.key_hash) ? (*bean.key_hash) : std::string("")),
                  bean.name, bean.user_hash, bean.value);

      return *bean.key_hash;
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void insert_with_pk(PostgresTransactionImpl *tr, KeyBean bean) {
    try {
      const char *query = "INSERT INTO public.key (\"key_hash\", \"name\", "
                          "\"user_hash\", \"value\") VALUES ($1, $2, $3, $4)";

      tr->execute(query, ((bean.key_hash) ? (*bean.key_hash) : std::string("")),
                  bean.name, bean.user_hash, bean.value);

    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }

  static void update(PostgresTransactionImpl *tr, KeyBean bean) {
    try {
      std::string setBuilder = "";
      setBuilder +=
          ((setBuilder != "") ? std::string(", ") : std::string("")) +
          Format::format(std::string("\"name\" = '%s'"), bean.name.c_str());
      setBuilder += ((setBuilder != "") ? std::string(", ") : std::string("")) +
                    Format::format(std::string("\"user_hash\" = '%s'"),
                                   bean.user_hash.c_str());
      setBuilder +=
          ((setBuilder != "") ? std::string(", ") : std::string("")) +
          Format::format(std::string("\"value\" = '%s'"), bean.value.c_str());
      std::string query_template = Format::format(
          "UPDATE public.key SET %s WHERE key_hash = $1", setBuilder.c_str());
      const char *query = query_template.c_str();

      tr->execute(query, *bean.key_hash);
    } catch (std::exception &e) {
      std::cout << "exception: " << e.what() << std::endl;
    }
  }
  /*
      static void override(PostgresTransactionImpl* tr, KeyBean bean)
      {
          try
          {
              const char * query = "UPDATE public.key SET key_hash = $1, name =
  $2, user_hash = $3, value = $4 WHERE key_hash = ?";

              int bindIndex = 1;

              query.bind(bindIndex++, bean.name);
  query.bind(bindIndex++, bean.user_hash);
  query.bind(bindIndex++, bean.value);

              query.bind(bindIndex++, *bean.key_hash);

              query.exec();
          }
          catch (std::exception& e)
          {
              std::cout << "exception: " << e.what() << std::endl;
          }
      }*/
};
