// This file is a part of quicksave project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#pragma once

#include <folly/Memory.h>
#include <proxygen/httpserver/RequestHandler.h>

class ProxygenHandler : public proxygen::RequestHandler
{
public:
    void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;

    void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;

    void onEOM() noexcept override;

    void onUpgrade(proxygen::UpgradeProtocol proto) noexcept override;

    void requestComplete() noexcept override;

    void onError(proxygen::ProxygenError err) noexcept override;

    virtual void handle() = 0;
    virtual void reply(int statusCode) = 0;
    virtual void reply(const char *message) = 0;
    virtual void reply_options() = 0;

protected:
    std::unique_ptr<proxygen::HTTPMessage> headers_;
    std::unique_ptr<folly::IOBuf> body_;
    std::unique_ptr<folly::IOBuf> response;
    int statusCode;
};

#include <proxygen/httpserver/RequestHandler.h>

#include <proxygen/httpserver/ResponseBuilder.h>
#include <util/format.h>
#include <util/logger.h>
#include <timer>

void ProxygenHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept
{
    TIC;
    headers_ = std::move(headers);
    Logger::log(Logger::format("%s %s", headers_->getMethodString().c_str(), headers_->getPath().c_str()));
}

void ProxygenHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept
{
    if (body_)
    {
        body_->prependChain(std::move(body));
    }
    else
    {
        body_ = std::move(body);
    }
}

void ProxygenHandler::onEOM() noexcept
{
    if (body_)
    {
        std::string buf{reinterpret_cast<const char *>(body_->data()), body_->length()};
        Logger::log(Logger::format("< %s [%luB]", buf.c_str(), body_->length()));

        handle();
        TAC;
    }
    else
    {
        TAC;
        if (headers_->getMethodString() == "OPTIONS")
            return reply_options();
        return reply(400);
    }
}

void ProxygenHandler::onUpgrade(proxygen::UpgradeProtocol protocol) noexcept
{
    // handler doesn't support upgrades
}

void ProxygenHandler::requestComplete() noexcept
{
    delete this;
}

void ProxygenHandler::onError(proxygen::ProxygenError err) noexcept
{
    delete this;
}

