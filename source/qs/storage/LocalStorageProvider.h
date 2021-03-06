// This file is a part of quicksave project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#pragma once

#include <qs/storage/StorageProvider.h>
#include <qs/storage/LocalStorage.h>
#include <absl/strings/string_view.h>

namespace storage {

class LocalStorageProvider : public storage::StorageProvider
{
public:
    bool validate(const std::string& storageConnectionString) const override
    {
        static const std::string acceptingProtocolString = "file://";
        static const size_t acceptingProtocolStringSize = acceptingProtocolString.size();

        if (storageConnectionString.size() < acceptingProtocolStringSize)
        {
            return false;
        }
        else
        {
            absl::string_view connectionProtocolString = {&storageConnectionString[0], acceptingProtocolStringSize};
            return connectionProtocolString == acceptingProtocolString;
        }
    }

    std::unique_ptr<storage::Storage> accept(RequestContext &ctx, const std::string& storageConnectionString) const override
    {
        static const std::string acceptingProtocolString = "file://";
        static const size_t acceptingProtocolStringSize = acceptingProtocolString.size();

        std::string connectionString(&storageConnectionString[acceptingProtocolString.size()], storageConnectionString.size() - acceptingProtocolString.size());
        return std::unique_ptr<storage::Storage>(new storage::LocalStorage(ctx, connectionString));
    }
};
}
