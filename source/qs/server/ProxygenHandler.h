// This file is a part of quicksave project.
// Copyright (c) 2017 Aleksander Gajewski <adiog@quicksave.io>.

#pragma once

#include <folly/Format.h>
#include <folly/Memory.h>

#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>

#include <style>
#include <timer>
#include <qs/server/HttpStatusCodeMapping.h>
#include <qs/util/buffer.h>


class ProxygenHandler : public proxygen::RequestHandler
{
public:
    void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;

    void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;

    void onEOM() noexcept override;

    void onUpgrade(proxygen::UpgradeProtocol proto) noexcept override;

    void requestComplete() noexcept override;

    void onError(proxygen::ProxygenError err) noexcept override;

    virtual void handle_get() abstract;

    virtual void handle_post() abstract;

    virtual void handle_options();

    void reply(int statusCode);

    void reply_cookie(int statusCode, const std::string& cookieName, const std::string& cookieValue);

    void reply_response(std::unique_ptr<folly::IOBuf>& response);

    std::string formatSetCookie(const std::string& cookieName, const std::string& cookieValue);

private:
    MEASURE;

protected:
    std::unique_ptr<proxygen::HTTPMessage> headers_;
    std::unique_ptr<folly::IOBuf> body_;
};


void ProxygenHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept
{
    headers_ = std::move(headers);
    LOG(INFO) << folly::format("{} {}", headers_->getMethodString().c_str(), headers_->getPath().c_str());
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
    const std::string& method = headers_->getMethodString();

    if (method == "POST")
    {
        return handle_post();
    }
    else if (method == "GET")
    {
        return handle_get();
    }
    else if (method == "OPTIONS")
    {
        return handle_options();
    }
    else
    {
        return reply(400);
    }
}

void ProxygenHandler::onUpgrade(proxygen::UpgradeProtocol protocol) noexcept
{
    // handler doesn"t support upgrades
}

void ProxygenHandler::requestComplete() noexcept
{
    delete this;
}

void ProxygenHandler::onError(proxygen::ProxygenError err) noexcept
{
    delete this;
}

void ProxygenHandler::handle_options()
{
    // TODO: verify domain
    int statusCode = 200;
    const char* statusText = "OK";

    LOG(INFO) << folly::format("> {}", statusCode);

    proxygen::ResponseBuilder(downstream_)
        .status(statusCode, statusText)
        .header("Vary", "Accept-Encoding, Origin")
        .header("Keep-Alive", "timeout=5, max=100")
        .header("Connection", "Keep-Alive")
        .header("Content-Type", "text/plain")
        .sendWithEOM();
}

std::string ProxygenHandler::formatSetCookie(const std::string& cookieName, const std::string& cookieValue)
{
    if (cookieValue == "")
    {
        return folly::format("{}=; HttpOnly; Path=/; expires=Thu, 01 Jan 1970 00:00:00 GMT", cookieName.c_str()).str();
    }
    else
    {
        return folly::format("{}={}; HttpOnly; Path=/", cookieName.c_str(), cookieValue.c_str()).str();
    }
}

void ProxygenHandler::reply_cookie(int statusCode, const std::string& cookieName, const std::string& cookieValue)
{
    const std::string setCookie = formatSetCookie(cookieName, cookieValue);

    LOG(INFO) << folly::format("> {} {}", statusCode, setCookie.c_str());

    if (statusCode == 200)
    {
        proxygen::ResponseBuilder(downstream_)
            .status(200, "OK")
            .header("Content-Type", "application/json")
            .header("Vary", "Cookie")
            .header("Set-Cookie", setCookie.c_str())
            .body("{}")
            .sendWithEOM();
    }
    else
    {
        proxygen::ResponseBuilder(downstream_)
            .status(statusCode, qs::server::HttpStatusCodeMapping::getReasonPhrase(statusCode))
            .header("Vary", "Cookie")
            .header("Set-Cookie", setCookie.c_str())
            .sendWithEOM();
    }
}

void ProxygenHandler::reply(int statusCode)
{
    LOG(INFO) << folly::format("> {}", statusCode);

    if (statusCode == 200)
    {
        proxygen::ResponseBuilder(downstream_)
            .status(200, "OK")
            .header("Content-Type", "application/json")
            .body("{}")
            .sendWithEOM();
    }
    else
    {
        proxygen::ResponseBuilder(downstream_)
            .status(statusCode, qs::server::HttpStatusCodeMapping::getReasonPhrase(statusCode))
            .sendWithEOM();
    }
}

void ProxygenHandler::reply_response(std::unique_ptr<folly::IOBuf>& response)
{
    std::string buffer = qs::util::Buffer::to_string(response);
    LOG(INFO) << folly::format("> 200 [{}B] {}", response->length(), buffer.c_str());

    proxygen::ResponseBuilder(downstream_)
        .status(200, "OK")
        .header("Content-Type", "application/json")
        .body(buffer)
        .sendWithEOM();
}
